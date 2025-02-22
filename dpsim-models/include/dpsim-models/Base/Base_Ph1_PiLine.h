/* Copyright 2017-2021 Institute for Automation of Complex Power Systems,
 *                     EONERC, RWTH Aachen University
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *********************************************************************************/

#pragma once

#include <dpsim-models/Definitions.h>
#include <dpsim-models/AttributeList.h>

namespace CPS {
namespace Base {
namespace Ph1 {
	class PiLine {

	public:
		/// Resistance along the line [ohms]
		const Attribute<Real>::Ptr mSeriesRes;
		/// Inductance along the line [H]
		const Attribute<Real>::Ptr mSeriesInd;
		/// Capacitance in parallel to the line [F]
		const Attribute<Real>::Ptr mParallelCap;
		/// Conductance in parallel to the line [S]
		const Attribute<Real>::Ptr mParallelCond;

		explicit PiLine(CPS::AttributeBase::Map &attributeList) :
			mSeriesRes(Attribute<Real>::create("R_series", attributeList)),
			mSeriesInd(Attribute<Real>::create("L_series", attributeList)),
			mParallelCap(Attribute<Real>::create("C_parallel", attributeList)),
			mParallelCond(Attribute<Real>::create("G_parallel", attributeList)) { };

		///
		void setParameters(Real seriesResistance, Real seriesInductance,
			Real parallelCapacitance = 0, Real parallelConductance = 0) const {
			**mSeriesRes = seriesResistance;
			**mSeriesInd = seriesInductance;
			**mParallelCond = parallelConductance;
			**mParallelCap = parallelCapacitance;
		}
	};
}
}
}
