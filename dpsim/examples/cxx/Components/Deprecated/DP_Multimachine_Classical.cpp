﻿/* Copyright 2017-2021 Institute for Automation of Complex Power Systems,
 *                     EONERC, RWTH Aachen University
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *********************************************************************************/

#include <DPsim.h>

using namespace DPsim;
using namespace DPsim::DP::Ph1;

int main(int argc, char* argv[]) {
	// Define machine parameters in per unit
	Real nomPower = 555e6;
	Real nomPhPhVoltRMS = 24e3;
	Real nomFreq = 60;
	Real nomFieldCurr = 1300;
	Int poleNum = 2;
	Real J = 2.8898e+04;
	Real H = 3.7;

	Real Rs = 0.003;
	Real Ll = 0.15;
	Real Lmd = 1.6599;
	Real Lmd0 = 1.6599;
	Real Lmq = 1.61;
	Real Lmq0 = 1.61;
	Real Rfd = 0.0006;
	Real Llfd = 0.1648;
	Real Rkd = 0.0284;
	Real Llkd = 0.1713;
	Real Rkq1 = 0.0062;
	Real Llkq1 = 0.7252;
	Real Rkq2 = 0.0237;
	Real Llkq2 = 0.125;
	//Real Rkq2 = 0;
	//Real Llkq2 = 0;

	//Exciter
	Real Ka = 20;
	Real Ta = 0.2;
	Real Ke = 1;
	Real Te = 0.314;
	Real Kf = 0.063;
	Real Tf = 0.35;
	Real Tr = 0.02;

	// Turbine
	Real Ta_t = 0.3;
	Real Fa = 0.3;
	Real Tb = 7;
	Real Fb = 0.3;
	Real Tc = 0.2;
	Real Fc = 0.4;
	Real Tsr = 0.1;
	Real Tsm = 0.3;
	Real Kg = 20;

	// Set up simulation
	Real tf, dt, t;
	Real om = 2.0*M_PI*60.0;
	tf = 0.3; dt = 0.00005; t = 0;
	Int downSampling = 1;

	Real Ld_s = 0.23;
	Real Lq_s = 0.25;
	Real Ra = (Ld_s + Lq_s) / dt;

	// Declare circuit components
	String mGeneratorName = "DP_Dq_" + std::to_string(dt);
	Component::Ptr gen = SynchronGenerator::make(mGeneratorName, 0, 1, 2,
			nomPower, nomPhPhVoltRMS, nomFreq, poleNum, nomFieldCurr,
			Rs, Ll, Lmd, Lmd0, Lmq, Lmq0, Rfd, Llfd, Rkd, Llkd, Rkq1, Llkq1, Rkq2, Llkq2, H, Ra, Logger::Level::info);

	// Declare circuit components
	String mGeneratorName2 = "DP_Dq2_" + std::to_string(dt);
	Component::Ptr gen2 = SynchronGenerator::make(mGeneratorName2, 12, 13, 14,
			nomPower, nomPhPhVoltRMS, nomFreq, poleNum, nomFieldCurr,
			Rs, Ll, Lmd, Lmd0, Lmq, Lmq0, Rfd, Llfd, Rkd, Llkd, Rkq1, Llkq1, Rkq2, Llkq2, H, Ra, Logger::Level::info);

	Real loadRes = 0.96;
	Real lineRes = 0.032;
	Real lindeInd = 0.35 / (2 * PI * 60);
	Real Rsn = 25;
	Real Res = 1e10;

	// Line Resistance
	Component::Ptr LineR1 = Resistor::make("LineR1", 0, 3, lineRes);
	Component::Ptr LineR2 = Resistor::make("LineR2", 1, 4, lineRes);
	Component::Ptr LineR3 = Resistor::make("LineR3", 2, 5, lineRes);

	// Line Resistance
	Component::Ptr Res1 = Resistor::make("Res1", 0, 6, Res);
	Component::Ptr Res2 = Resistor::make("Res2", 1, 7, Res);
	Component::Ptr Res3 = Resistor::make("Res3", 2, 8, Res);

	// Snubber Resistance
	Component::Ptr Rsn1 = Resistor::make("Rsn1", 0, GND, Rsn);
	Component::Ptr Rsn2 = Resistor::make("Rsn2", 1, GND, Rsn);
	Component::Ptr Rsn3 = Resistor::make("Rsn3", 2, GND, Rsn);

	// Line Inductance
	Component::Ptr LineL1 = Inductor::make("LineL1", 3, 6, lindeInd);
	Component::Ptr LineL2 = Inductor::make("LineL2", 4, 7, lindeInd);
	Component::Ptr LineL3 = Inductor::make("LineL3", 5, 8, lindeInd);

	// Load
	Component::Ptr r1 = Resistor::make("r1", 6, GND, loadRes);
	Component::Ptr r2 = Resistor::make("r2", 7, GND, loadRes);
	Component::Ptr r3 = Resistor::make("r3", 8, GND, loadRes);

	// Line Inductance2
	Component::Ptr LineL12 = Inductor::make("LineL12", 6, 9, lindeInd);
	Component::Ptr LineL22 = Inductor::make("LineL22", 7, 10, lindeInd);
	Component::Ptr LineL32 = Inductor::make("LineL32", 8, 11, lindeInd);

	// Line Resistance2
	Component::Ptr LineR12 = Resistor::make("LineR12", 9, 12, lineRes);
	Component::Ptr LineR22 = Resistor::make("LineR22", 10, 13, lineRes);
	Component::Ptr LineR32 = Resistor::make("LineR32", 11, 14, lineRes);

	// Line Resistance
	Component::Ptr Rsn4 = Resistor::make("Rsn4", 12, GND, Rsn);
	Component::Ptr Rsn5 = Resistor::make("Rsn5", 13, GND, Rsn);
	Component::Ptr Rsn6 = Resistor::make("Rsn6", 14, GND, Rsn);

	// Line Resistance
	Component::Ptr Res12 = Resistor::make("Res12", 6, 12, Res);
	Component::Ptr Res22 = Resistor::make("Res22", 7, 13, Res);
	Component::Ptr Res32 = Resistor::make("Res32", 8, 14, Res);

	SystemComponentList comps = { gen, gen2, LineR1, LineR2, LineR3, LineL1, LineL2, LineL3, r1, r2, r3,
		Res1, Res2, Res3, LineR12, LineR22, LineR32, LineL12, LineL22, LineL32, Res12, Res22, Res32, Rsn1, Rsn2, Rsn3, Rsn4, Rsn5, Rsn6 };

	// Declare circuit components for resistance change
	Real breakerRes = 9.6 + 0.0001;
	Component::Ptr rBreaker1 = Resistor::make("rbreak1", 6, GND, breakerRes);
	Component::Ptr rBreaker2 = Resistor::make("rbreak2", 7, GND, breakerRes);
	Component::Ptr rBreaker3 = Resistor::make("rbreak3", 8, GND, breakerRes);

	SystemComponentList compsBreakerOn = { gen, gen2, LineR1, LineR2, LineR3, LineL1, LineL2, LineL3,
			r1,	r2, r3, Res1, Res2, Res3, LineR12, LineR22, LineR32, LineL12, LineL22, LineL32,
			Res12, Res22, Res32, rBreaker1, rBreaker2, rBreaker3, Rsn1, Rsn2, Rsn3, Rsn4, Rsn5, Rsn6 };

	String mSimulationName = "DP_SynchronGenerator_Dq_" + std::to_string(dt);
	SynGenSimulation sim(mSimulationName, Logger::Level::info);
	sim.setSystem(comps);
	sim.setTimeStep(dt);
	sim.setFinalTime(tf);
	sim.setDomain(Domain::DP);
	sim.setSolverType(Solver::Type::MNA);
	sim.setNumericalMethod(NumericalMethod::Trapezoidal_flux);
	sim.addSystemTopology(compsBreakerOn);
	sim.switchSystemMatrix(0);

	// Initialize generator
	Real initActivePower = 285.89e6;
	Real initReactivePower = 0;
	Real initTerminalVolt = 24000 / sqrt(3) * sqrt(2);
	Real initVoltAngle = -DPS_PI / 2;
	Real mechPower = 285.89e6;
	auto genPtr = std::dynamic_pointer_cast<DP::Ph3SynchronGenerator>(gen);
	genPtr->initialize(om, dt, initActivePower, initReactivePower, initTerminalVolt, initVoltAngle, mechPower);
	genPtr->AddExciter(Ta, Ka, Te, Ke, Tf, Kf, Tr, Lmd, Rfd);
	genPtr->AddGovernor(Ta_t, Tb, Tc, Fa, Fb, Fc, Kg, Tsr, Tsm, initActivePower / nomPower, mechPower / nomPower);

	auto genPtr2 = std::dynamic_pointer_cast<DP::Ph3SynchronGenerator>(gen2);
	genPtr2->initialize(om, dt, initActivePower, initReactivePower, initTerminalVolt, initVoltAngle, mechPower);
	genPtr2->AddExciter(Ta, Ka, Te, Ke, Tf, Kf, Tr, Lmd, Rfd);
	genPtr2->AddGovernor(Ta_t, Tb, Tc, Fa, Fb, Fc, Kg, Tsr, Tsm, initActivePower / nomPower, mechPower / nomPower);

	std::cout << "A matrix:" << std::endl;
	std::cout << sim.systemMatrix() << std::endl;
	std::cout << "vt vector:" << std::endl;
	std::cout << sim.leftSideVector() << std::endl;
	std::cout << "j vector:" << std::endl;
	std::cout << sim.rightSideVector() << std::endl;

	Real lastLogTime = 0;
	Real logTimeStep = 0.00005;
	sim.setSwitchTime(0.1, 1);
	sim.setSwitchTime(0.2, 0);

	sim.run();

	return 0;
}
