#define CATCH_CONFIG_MAIN

#include <iostream>
#include "../../catch2/catch.hpp"
#include "Car.h"

TEST_CASE("Car must stand by default")
{
	CCar car;
	CHECK(car.GetDirection() == Direction::STAND);
}

TEST_CASE("Speed must be in range of curent gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);

	CHECK(car.SetSpeed(30));

	CHECK(car.SetSpeed(0));

	CHECK(!car.SetSpeed(-1));
	
	CHECK(!car.SetSpeed(31));
}

TEST_CASE("The car cannot accelerate in neutral gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetSpeed(20);
	car.SetGear(0);

	CHECK(!car.SetSpeed(30));
}

TEST_CASE("If car speed != 0 and gear >= 1 diraction must be forward")
{
	CCar car;
	car.TurnOnEngine();
	
	CHECK(car.GetDirection() == Direction::STAND);
	car.SetGear(1);
	car.SetSpeed(10);
	CHECK(car.GetDirection() == Direction::FORWARD);
}

TEST_CASE("If car speed != 0 and gear = -1 diraction must be back")
{
	CCar car;
	car.TurnOnEngine();

	CHECK(car.GetDirection() == Direction::STAND);
	car.SetGear(-1);
	car.SetSpeed(10);
	CHECK(car.GetDirection() == Direction::BACK);
}

TEST_CASE("You can change the gear if current speed in speed range of new gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);

	car.SetSpeed(10);

	CHECK(!car.SetGear(2));
}

TEST_CASE("Engine must be turned off at zero speed in neutral gear")
{
	CCar car;
	car.TurnOnEngine();

	car.SetGear(1);
	car.SetSpeed(10);
	CHECK(!car.TurnOffEngine());

	car.SetGear(0);
	CHECK(!car.TurnOffEngine());

	car.SetSpeed(0);
	CHECK(car.TurnOffEngine());
}

TEST_CASE("If engine is off, only neutral gear can be")
{
	CCar car;

	CHECK(!car.SetGear(1));
	CHECK(!car.SetGear(-1));
	CHECK(car.SetGear(0));
}