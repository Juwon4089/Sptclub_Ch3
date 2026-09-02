#include "Sptclub_Ch3GameState.h"

ASptclub_Ch3GameState::ASptclub_Ch3GameState()
{
	Score = 0;
	CurrentWave = 0;
	TimeRemaining = 0.0f;
}

int32 ASptclub_Ch3GameState::GetScore() const
{
	return Score;
}

int32 ASptclub_Ch3GameState::GetCurrentWave() const
{
	return CurrentWave;
}

float ASptclub_Ch3GameState::GetTimeRemaining() const
{
	return TimeRemaining;
}

void ASptclub_Ch3GameState::AddScore(int32 Amount)
{
	Score = Score + Amount;
}

void ASptclub_Ch3GameState::SetCurrentWave(int32 NewWave)
{
	CurrentWave = NewWave;
}

void ASptclub_Ch3GameState::SetTimeRemaining(float NewTime)
{
	if (NewTime < 0.0f)
	{
		TimeRemaining = 0.0f;
	}
	else
	{
		TimeRemaining = NewTime;
	}
}
