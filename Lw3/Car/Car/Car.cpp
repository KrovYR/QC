#include "Car.h"

bool CCar::TurnOnEngine()
{
    m_isEngineOn = true;

    return true;
}


bool CCar::TurnOffEngine()
{
    if (m_gear != 0 || m_speed != 0)
        return false;

    m_isEngineOn = false;

    return true;
}


bool CCar::SetGear(Gear gear)
{
    if (!m_isEngineOn && gear != 0)
        return false;

    if (gear == m_gear)
        return true;

    if (gear == -1 && m_speed != 0)
        return false;

    if (gear >= 1 && m_direction == Direction::BACK && m_speed != 0)
        return false;

    const SpeedInterval speedIntervalForNewGear = m_speedIntervals.at(gear);
    const Speed minSpeed = speedIntervalForNewGear.first;
    const Speed maxSpeed = speedIntervalForNewGear.second;

    if (m_speed < minSpeed || m_speed > maxSpeed)
        return false;

    m_gear = gear;

    SetDirection();

    return true;
}


bool CCar::SetSpeed(Speed speed)
{
    if (!m_isEngineOn)
        return false;

    if (m_gear < -1 || m_gear > 5)
        return false;

    if (speed < 0 || speed > 150)
        return false;

    if (m_gear == 0 && speed > m_speed)
        return false;

    if (speed == m_speed)
        return true;

    const SpeedInterval speedIntervalForCurrentGear = m_speedIntervals.at(m_gear);
    const Speed minSpeed = speedIntervalForCurrentGear.first;
    const Speed maxSpeed = speedIntervalForCurrentGear.second;

    if (m_gear != 0 && (speed < minSpeed || speed > maxSpeed))
        return false;

    m_speed = speed;

    SetDirection();

    return true;
}

Gear CCar::GetGear()
{
    return m_gear;
}


Speed CCar::GetSpeed()
{
    return m_speed;
}

Direction CCar::GetDirection()
{
    return m_direction;
}

void CCar::SetDirection()
{
    if (m_gear == -1 && m_speed != 0)
    {
        m_direction = Direction::BACK;
        return;
    }

    if (m_gear == 0 && m_direction == Direction::BACK && m_speed != 0)
    {
        m_direction = Direction::BACK;
        return;
    }

    if (m_speed == 0)
    {
        m_direction = Direction::STAND;
        return;
    }

    m_direction = Direction::FORWARD;
}