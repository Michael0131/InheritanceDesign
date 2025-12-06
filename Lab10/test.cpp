/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/


#include "testPosition.h"
#include "testVelocity.h"
#include "testEntity.h"
#include "testSatellite.h"
#include "testPhysics.h"
#include "testGPS.h"
#include "testCrewDragon.h"
#include "testHubble.h"
#include "testSputnik.h"
#include "testBullet.h"
#include "testDreamChaser.h"

#include "testPart.h"
#include "testFragment.h"
#include "testCollision.h"

#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
#ifdef _WIN32
	AllocConsole();
	FILE* stream;
	errno_t err;
	err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32

	TestPosition().run();
	TestVelocity().run();
	TestEntity().run();
	TestSatellite().run();
	TestPhysics().run();
	TestGPS().run();
	TestCrewDragon().run();
	TestHubble().run();
	TestSputnik().run();
	TestDreamChaser().run();
	TestBullet().run();

	TestFragment().run();
	TestPart().run();
	TestCollision().run();
}
