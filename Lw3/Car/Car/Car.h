#pragma once

#include <string>;
#include <unordered_map>;

enum class Direction
{
	BACK,
	STAND,
	FORWARD
};

using Gear = short;
using Speed = short;
using SpeedInterval = std::pair<Speed, Speed>;

const bool INITIAL_ENGINE_STATE = false;
const Gear INITIAL_GEAR = 0;
const Speed INITIAL_SPEED = 0;
const Direction INITIAL_DIRECTION = Direction::STAND;

class CCar
{
public:
	CCar() = default;
	~CCar() = default;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(Gear gear);
	Gear GetGear();

	bool SetSpeed(Speed speed);
	Speed GetSpeed();

	Direction GetDirection();

private:
	bool m_isEngineOn = false;
	Gear m_gear = 0;
	Speed m_speed = 0;
	Direction m_direction = Direction::STAND;

	void SetDirection();

	const std::unordered_map<Gear, SpeedInterval> m_speedIntervals{
		{ -1, { 0, 20 } },
		{ 0, { 0, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } },
	};
};