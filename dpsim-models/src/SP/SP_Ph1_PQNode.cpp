/* Copyright 2017-2021 Institute for Automation of Complex Power Systems,
 *                     EONERC, RWTH Aachen University
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *********************************************************************************/

#include <dpsim-models/SP/SP_Ph1_PQNode.h>

using namespace CPS;

 SP::Ph1::PQNode::PQNode(String uid, String name,
	 Logger::Level logLevel)
	 : SimPowerComp<Complex>(uid, name, logLevel),
	 mPower(Attribute<Real>::create("P", mAttributes)),
	 mReactivePower(Attribute<Real>::create("Q", mAttributes)),
	 mPowerNom(Attribute<Real>::create("P_nom", mAttributes)),
	 mReactivePowerNom(Attribute<Real>::create("Q_nom", mAttributes)) {}

 SP::Ph1::PQNode::PQNode(String uid, String name, Real power, Real reactive_power,
	 Logger::Level logLevel):PQNode(uid,name,logLevel) {

	 **mPower = power;
	 **mPowerNom = power;
	 **mReactivePower = reactive_power;
	 **mReactivePowerNom = reactive_power;

     mSLog->info("Create PQ node for {} P={}, Q={}", name, **mPowerNom, **mReactivePowerNom);

 }

