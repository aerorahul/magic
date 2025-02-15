// (C) Copyright 2019- NOAA/NWS/NCEP/EMC

#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

namespace eckit {
  class Configuration;
}

namespace oops {
  class Variables;
}

// namespace ufo {
//   class GeoVaLs;
//   class Locations;
// }

namespace magic {
  class Geometry;
  class Increment;

// -----------------------------------------------------------------------------
/// State handles model state and everything needed to propagate forward

  class State : public util::Printable,
                private util::ObjectCounter<State> {
   public:
      static const std::string classname() {return "magic::State";}

      /// Constructor, destructor
      State(const Geometry &, const oops::Variables &,
            const util::DateTime &);
      State(const Geometry &, const eckit::Configuration &);
      State(const Geometry &, const State &);
      State(const State &);
      virtual ~State();

      /// Basic operators
      State & operator=(const State &);

      /// Get state values at observation locations
//      void getValues(const ufo::Locations &,
//                     const oops::Variables &,
//                     ufo::GeoVaLs &) const;

      /// Interactions with Increment
      State & operator+=(const Increment &);

      /// I/O and diagnostics
      void read(const eckit::Configuration &);
      void write(const eckit::Configuration &) const;

      /// Access to fields
      const oops::Variables & variables() const {return vars_;}

      /// Serialize and deserialize
      size_t serialSize() const;
      void serialize(std::vector<double> &) const;
      void deserialize(const std::vector<double> &, size_t &);

      std::shared_ptr<const Geometry> geometry() const {return geom_;}
      const util::DateTime & validTime() const {return time_;}
      util::DateTime & validTime() {return time_;}
      void updateTime(const util::Duration & dt) {time_ += dt;}

      /// Other
      double norm() const;
      void zero();
      void accumul(const double &, const State &);

   private:
      void print(std::ostream &) const;
      std::shared_ptr<const Geometry> geom_;
      oops::Variables vars_;
      util::DateTime time_;
  };
// -----------------------------------------------------------------------------

}  // namespace magic
