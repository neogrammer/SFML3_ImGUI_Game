#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <FSM/DuckFold.h>
#include <optional>

#include <type_traits>
#include <variant>
#include <iostream>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:

	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "Moving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "Shooting" << std::endl; return StartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedJumping& e) { std::cout << "StartedJump" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventLifeDepleted& e) { std::cout << "Dead" << std::endl; return DeadState{}; }

	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedJumping& e) { std::cout << "StartedJumpAndShooting" << std::endl; return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }


	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStartedShooting& e) { std::cout << "MovingAndStartedShooting" << std::endl; return MovingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStartedJumping& e) { std::cout << "MovingAndStartedJump" << std::endl; return MovingAndStartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	

	std::optional<PlayerAnimVar> On_Event(StartedJumpState& s, const EventStartedShooting& e) { std::cout << "StartedJumpAndStartedShooting" << std::endl; return StartedJumpAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpState& s, const EventStartedMoving& e) { std::cout << "MovingAndStartedJump" << std::endl; return MovingAndStartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	

	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventStartedShooting& e) { std::cout << "RisingAndStartedShootingState" << std::endl; return RisingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventNearingTopOfJump& e) { std::cout << "AtJumpTopState" << std::endl; return AtJumpTopState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventFell& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventReachedJumpHeight& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopState& s, const EventStartedShooting& e) { std::cout << "AtJumpTopAndStartedShootingState" << std::endl; return AtJumpTopAndStartedShootingState{}; }


	
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventStartedShooting& e) { std::cout << "FallingAndStartedShootingState" << std::endl; return FallingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState & s, const EventLanding & e) { std::cout << "LandingState" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventLifeDepleted& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }

	
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedShooting& e) { std::cout << "LandingAndStartedShootingState" << std::endl; return LandingAndStartedShootingState{}; } 
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedMoving& e) { std::cout << "MovingAndLandingState" << std::endl; return MovingAndLandingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventLanding2& e) { std::cout << "IdleState" << std::endl;  return IdleState{}; } 
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventFell &e) { std::cout << "FallingState" << std::endl; return FallingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStartedJumping& e) { std::cout << "MovingAndStartedJumpAndShootingState" << std::endl;  return MovingAndStartedJumpAndShootingState{};  }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShootingState" << std::endl;  return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "MovingState" << std::endl;  return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "ShootingState" << std::endl;  return ShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventStoppedShooting& e) { std::cout << "StartedJumpState" << std::endl;  return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndStartedJumpAndShootingState" << std::endl;  return MovingAndStartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventJumpStartFinished& e) { std::cout << "RisingAndShootingState" << std::endl;  return RisingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpState& s, const EventStoppedMoving& e) { std::cout << "StartedJumpState" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpState& s, const EventStartedShooting& e) { std::cout << "MovingAndStartedJumpAndStartedShootingState" << std::endl; return MovingAndStartedJumpAndStartedShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndShootingState& s, const EventStoppedShooting& e) { std::cout << "MovingAndStartedJumpState" << std::endl; return MovingAndStartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndShootingState& s, const EventStoppedMoving& e) { std::cout << "StartedJumpAndShootingState" << std::endl; return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "RisingState" << std::endl; return RisingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventNearingTopOfJump& e) { std::cout << "AtJumpTopAndShootingState" << std::endl; return AtJumpTopAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndShootingState& s, const EventStoppedShooting& e) { std::cout << " AtJumpTopState" << std::endl; return AtJumpTopState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndShootingState& s, const EventReachedJumpHeight& e) { std::cout << "FallingAndShootingState" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }


	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLanding& e) { std::cout << "LandingAndShootingState" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLifeDepleted& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }

	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "LandingState" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventLanding2& e) { std::cout << "ShootingState" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShootingState" << std::endl; return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndLandingState& s, const EventLanding2& e) { std::cout << "MovingState" << std::endl;  return MovingState{}; } 
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; } 
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingState& s, const EventStoppedMoving& e) { std::cout << "LandingState" << std::endl;  return LandingState{}; } 
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingState& s, const EventStartedShooting& e) { std::cout << "MovingAndLandingAndStartedShootingState" << std::endl;  return MovingAndLandingAndStartedShootingState{}; } 
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingState& s, const EventFell& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "MovingAndLandingState" << std::endl;  return MovingAndLandingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "LandingAndShootingState" << std::endl;  return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndShootingState& s, const EventLanding2& e) { std::cout << "MovingAndShootingState" << std::endl;  return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShootingState" << std::endl;  return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventShootSetupDone& e) { std::cout << "ShootingState" << std::endl;  return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventFell& e) { std::cout << "FallingAndShootingState" << std::endl;  return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventStoppedShooting& e) { std::cout << "IdleState" << std::endl;  return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventStartedMoving e) { std::cout << "MovingAndStartedShootingState" << std::endl;  return MovingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedShootingState& s, const EventStartedJumping e) { std::cout << "StartedJumpAndStartedShootingState" << std::endl;  return StartedJumpAndStartedShootingState{}; }


	std::optional<PlayerAnimVar> On_Event(MovingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "MovingAndShootingState" << std::endl;  return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "MovingState" << std::endl;  return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedShootingState& s, const EventStartedJumping& e) { std::cout << "MovingAndStartedJumpAndStartedShootingState" << std::endl;  return MovingAndStartedJumpAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedShootingState& s, const EventFell& e) { std::cout << "FallingAndStartedShootingState" << std::endl;  return FallingAndStartedShootingState{}; }


	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "MovingAndStartedJumpAndShootingState" << std::endl;  return MovingAndStartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "MovingAndStartedJumpState" << std::endl;  return MovingAndStartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndStartedShootingState& s, const EventStoppedMoving& e) { std::cout << "StartedJumpAndStartedShootingState" << std::endl;  return StartedJumpAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndStartedJumpAndStartedShootingState& s, const EventJumpStartFinished& e) { std::cout << "RisingAndStartedShootingState" << std::endl;  return RisingAndStartedShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedJumpAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "StartedJumpAndShootingState" << std::endl;  return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndStartedShootingState& s, const EventJumpStartFinished& e) { std::cout << "RisingAndStartedShootingState" << std::endl;  return RisingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "StartedJumpState" << std::endl;  return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndStartedShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndStartedJumpAndStartedShootingState" << std::endl;  return MovingAndStartedJumpAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(LandingAndStartedShootingState& s, const EventLanding2& e) { std::cout << "StartedShootingState" << std::endl;  return StartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "LandingAndShootingState" << std::endl;  return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndStartedShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndLandingAndStartedShootingState" << std::endl;  return MovingAndLandingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndStartedShootingState& s, const EventFell& e) { std::cout << "FallingAndStartedShootingState" << std::endl;  return FallingAndStartedShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "MovingAndLandingAndShootingState" << std::endl;  return MovingAndLandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndStartedShootingState& s, const EventFell& e) { std::cout << "FallingAndStartedShootingState" << std::endl;  return FallingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl;  return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndStartedShootingState& s, const EventStoppedMoving& e) { std::cout << "LandingAndStartedShootingState" << std::endl;  return LandingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndStartedShootingState& s, const EventLanding2& e) { std::cout << "MovingAndStartedShootingState" << std::endl;  return MovingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndLandingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "MovingAndLandingState" << std::endl;  return MovingAndLandingState{}; }

	std::optional<PlayerAnimVar> On_Event(RisingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "RisingAndShootingState" << std::endl; return RisingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "RisingState" << std::endl; return RisingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndStartedShootingState& s, const EventNearingTopOfJump& e) { std::cout << "AtJumpTopAndStartedShootingState" << std::endl; return AtJumpTopAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(RisingAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndStartedShootingState& s, const EventReachedJumpHeight& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndStartedShootingState& s, const EventFell& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(AtJumpTopAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "AtJumpTopState" << std::endl; return AtJumpTopState{}; }

	std::optional<PlayerAnimVar> On_Event(FallingAndStartedShootingState& s, const EventHit& e) { std::cout << "HitState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndStartedShootingState& s, const EventLanding& e) { std::cout << "LandingAndStartedShootingState" << std::endl; return LandingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "FallingState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndStartedShootingState& s, const EventLifeDepleted& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStartedJumping& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStartedShooting& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return IdleState{}; }


	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingState& s, const EventStartedShooting& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndLandingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingState& s, const EventLanding2& e) { std::cout << "DeadState" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }


	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStartedJumping& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingAndStartedShootingState{}; }




	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingState & s, const EventStoppedMoving & e)   { std::cout << "DeadState" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return MovingAndStartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingState& s, const EventJumpStartFinished& e) { std::cout << "DeadState" << std::endl; return RisingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingState& s, const EventStartedShooting& e)    { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingState& s, const EventHit& e)                         { std::cout << "DeadState" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedShootingState& s, const  EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return StartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedShootingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return MovingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedShootingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return FallingAndStartedShootingState{}; }


	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventLanding2& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return MovingAndLandingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndLandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return LandingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndLandingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return FallingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndStartedShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }

	
	
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndShootingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndShootingState& s, const EventLanding2& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndShootingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndLandingAndShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return DeadState{}; }

	
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndStartedShootingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return MovingAndStartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndStartedShootingState& s, const EventJumpStartFinished& e) { std::cout << "DeadState" << std::endl; return RisingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndStartedShootingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return StartedJumpingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndStartedShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedJumpingAndStartedShootingState& s, const EventJumpStartFinished& e) { std::cout << "DeadState" << std::endl; return RisingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpingAndStartedShootingState& s, const EventShootSetupDone& e) { std::cout << "DeadState" << std::endl; return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpingAndStartedShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return StartedJumpState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpingAndStartedShootingState& s, const EventStartedMoving& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingAndStartedShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpingAndStartedShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedJumpingAndStartedShootingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return FallingAndStartedShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndShootingState& s, const EventHit& e) { std::cout << "DeadState" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "DeadState" << std::endl; return StartedMovingAndStartedJumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndShootingState& s, const EventJumpStartFinished& e) { std::cout << "DeadState" << std::endl; return RisingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndShootingState& s, const EventMoveStartFinished& e) { std::cout << "DeadState" << std::endl; return MovingAndStartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "DeadState" << std::endl; return StartedJumpAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndStartedJumpingAndShootingState& s, const EventFell& e) { std::cout << "DeadState" << std::endl; return FallingAndShootingState{}; }


	/*std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}*/
	template <typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&) { 	return std::nullopt; 	}
	std::string getStateName()
	{
		if (std::holds_alternative<IdleState>(state_)) { return "Idle"; }
		else if (std::holds_alternative<HitState>(state_)) { return "Hit"; }
		else if (std::holds_alternative<DeadState>(state_)) { return "Dead"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "Shooting"; }
		else if (std::holds_alternative<MovingState>(state_)) { return "Moving"; }
		else if (std::holds_alternative<StartedJumpState>(state_)) { return "StartedJump"; }
		else if (std::holds_alternative<RisingState>(state_)) { return "Rising"; }
		else if (std::holds_alternative<AtJumpTopState>(state_)) { return "AtJumpTop"; }
		else if (std::holds_alternative<FallingState>(state_)) { return "Falling"; }
		else if (std::holds_alternative<LandingState>(state_)) { return "Landing"; }
		else if (std::holds_alternative<MovingAndShootingState>(state_)) { return "MovingAndShooting"; }
		else if (std::holds_alternative<StartedJumpAndShootingState>(state_)) { return "StartedJumpAndShooting"; }
		else if (std::holds_alternative<MovingAndStartedJumpState>(state_)) { return "MovingAndStartedJumpAndShooting"; }
		else if (std::holds_alternative<MovingAndStartedJumpAndShootingState>(state_)) { return "MovingAndStartedJumpAndShooting"; }
		else if (std::holds_alternative<RisingAndShootingState>(state_)) { return "RisingAndShooting"; }
		else if (std::holds_alternative<AtJumpTopAndShootingState>(state_)) { return "AtJumpTopAndShooting"; }
		else if (std::holds_alternative<AtJumpTopState>(state_)) { return "AtJumpTop"; }
		else if (std::holds_alternative<FallingAndShootingState>(state_)) { return "FallingAndShooting"; }
		else if (std::holds_alternative<LandingAndShootingState>(state_)) { return "LandingAndShooting"; }
		else if (std::holds_alternative<MovingAndLandingState>(state_)) { return "MovingAndLanding"; }
		else if (std::holds_alternative<MovingAndLandingAndShootingState>(state_)) { return "MovingAndLandingAndShooting"; }
		else if (std::holds_alternative <StartedShootingState > (state_)) { return "StartedShooting"; }
		else if (std::holds_alternative <MovingAndStartedShootingState >(state_)) { return "MovingAndStartedShooting"; }
		else if (std::holds_alternative<FallingAndStartedShootingState>(state_)) { return "FallingAndStartedShooting"; }
		else if (std::holds_alternative<AtJumpTopAndStartedShootingState>(state_)) { return "AtJumpTopAndStartedShooting"; }
		else if (std::holds_alternative<RisingAndStartedShootingState>(state_)) { return "RisingAndStartedShooting"; }
		else if (std::holds_alternative<MovingAndLandingAndStartedShootingState>(state_)) { return "MovingAndLandingAndStartedShooting"; }
		else if (std::holds_alternative <LandingAndStartedShootingState >(state_)) { return "LandingAndStartedShooting"; }
		else if (std::holds_alternative <StartedJumpAndStartedShootingState >(state_)) { return "StartedJumpAndStartedShooting"; }
		else if (std::holds_alternative <MovingAndStartedJumpAndStartedShootingState >(state_)) { return "MovingAndStartedJumpAndStartedShooting"; }
		else if (std::holds_alternative <StartedMovingState>(state_)) { return "StartedMoving"; }
		else if (std::holds_alternative <StartedMovingAndLandingState >(state_)) { return "StartedMovingAndLanding"; }
		else if (std::holds_alternative <StartedMovingAndShootingState >(state_)) { return "StartedMovingAndShooting"; }
		else if (std::holds_alternative <StartedMovingAndStartedJumpingState >(state_)) { return "StartedMovingAndStartedJumping"; }
		else if (std::holds_alternative <StartedMovingAndStartedShootingState >(state_)) { return "StartedMovingAndStartedShooting"; }
		else if (std::holds_alternative <StartedMovingAndLandingAndStartedShootingState >(state_)) { return "StartedMovingAndLandingAndStartedShooting"; }
		else if (std::holds_alternative <StartedMovingAndStartedJumpingAndStartedShootingState >(state_)) { return "StartedMovingAndStartedJumpingAndStartedShooting"; }
		else if (std::holds_alternative <StartedMovingAndLandingAndShootingState >(state_)) { return "StartedMovingAndLandingAndShooting"; }
		else if (std::holds_alternative <StartedMovingAndStartedJumpingAndShootingState >(state_)) { return "StartedMovingAndStartedJumpingAndShooting"; }
		else if (std::holds_alternative <StartedJumpingAndStartedShootingState >(state_)) { return "StartedJumpingAndStartedShooting"; }
		else { return "None"; }
	}
};
#endif