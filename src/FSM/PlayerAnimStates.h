#pragma once
#include <FSM/IgnoreUnknownEvent.h>
#include <variant>
#include <FSM/Events.h>

struct IdleState {};
struct HitState {};
struct DeadState {};
struct ShootingState { };
struct MovingState {};
struct StartedJumpState {};
struct RisingState {};
struct AtJumpTopState {};
struct FallingState {};
struct MovingAndShootingState {};
struct LandingState {};
struct StartedJumpAndShootingState {};
struct StartedJumpAndStartedShootingState {};
struct MovingAndStartedJumpState {};
struct MovingAndStartedJumpAndShootingState {};
struct RisingAndStartedShootingState {};
struct RisingAndShootingState {};
struct AtJumpTopAndStartedShootingState {};
struct FallingAndStartedShootingState{};
struct AtJumpTopAndShootingState {};
struct FallingAndShootingState {};
struct LandingAndShootingState {};
struct MovingAndLandingState {};
struct MovingAndLandingAndShootingState {};
struct StartedShootingState {};
struct MovingAndStartedShootingState {};
struct LandingAndStartedShootingState{};
struct MovingAndStartedJumpAndStartedShootingState {};
struct MovingAndLandingAndStartedShootingState {};
struct StartedMovingState{};
struct StartedMovingAndLandingState {};
struct StartedMovingAndShootingState {};
struct StartedMovingAndStartedJumpingState {};
struct StartedMovingAndStartedShootingState{};
struct StartedMovingAndLandingAndStartedShootingState {};
struct StartedMovingAndStartedJumpingAndStartedShootingState {};
struct StartedMovingAndLandingAndShootingState {};
struct StartedMovingAndStartedJumpingAndShootingState {};
struct StartedJumpingAndStartedShootingState {};


using PlayerAnimVar = std::variant<IdleState, StartedMovingState, StartedMovingAndLandingAndShootingState, StartedJumpingAndStartedShootingState, StartedMovingAndStartedJumpingAndShootingState, StartedMovingAndStartedJumpingAndStartedShootingState, StartedMovingAndLandingAndStartedShootingState, StartedMovingAndStartedShootingState, StartedMovingAndLandingState, StartedMovingAndShootingState, StartedMovingAndStartedJumpingState , StartedJumpAndStartedShootingState,  MovingAndLandingAndStartedShootingState, MovingAndStartedJumpAndStartedShootingState, LandingAndStartedShootingState, AtJumpTopAndStartedShootingState, FallingAndStartedShootingState, RisingAndStartedShootingState,  ShootingState,  HitState, DeadState, MovingState, StartedJumpState, RisingState, FallingState, LandingState, MovingAndShootingState, StartedJumpAndShootingState, MovingAndStartedJumpState, MovingAndStartedJumpAndShootingState, RisingAndShootingState, AtJumpTopAndShootingState, AtJumpTopState, FallingAndShootingState, LandingAndShootingState, MovingAndLandingState, MovingAndLandingAndShootingState, StartedShootingState, MovingAndStartedShootingState>;

