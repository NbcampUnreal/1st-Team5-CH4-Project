#include "Character/Animation/GFAnimInstanceBase.h"
#include "Character/GFBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

float UGFAnimInstanceBase::CalculateDirection(const FVector& RVelocity, const FRotator& BaseRotation) const
{
	if (!RVelocity.IsNearlyZero())
	{
		FMatrix RotMatrix = FRotationMatrix(BaseRotation);
		FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
		FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
		FVector NormalizedVel = RVelocity.GetSafeNormal2D();

		// get a cos(alpha) of forward vector vs velocity
		float ForwardCosAngle = FVector::DotProduct(ForwardVector, NormalizedVel);
		// now get the alpha and convert to degree
		float ForwardDeltaDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));

		// depending on where right vector is, flip it
		float RightCosAngle = FVector::DotProduct(RightVector, NormalizedVel);
		if (RightCosAngle < 0)
		{
			ForwardDeltaDegree *= -1;
		}

		return ForwardDeltaDegree;
	}

	return 0.f;
}

void UGFAnimInstanceBase::NativeInitializeAnimation()
{
	OwnerPlayer = Cast<AGFBaseCharacter>(TryGetPawnOwner());
	if (OwnerPlayer)
	{
		PlayerMovement = OwnerPlayer->GetCharacterMovement();
	}
}

void UGFAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerPlayer == nullptr || PlayerMovement == nullptr)
		return;

	PlayerStateData.IsJump = false;
	PlayerStateData.WorldLocation = OwnerPlayer->GetActorLocation();
	PlayerStateData.Velocity = OwnerPlayer->GetVelocity();
	PlayerStateData.Velocity2D = PlayerStateData.Velocity * FVector(1.f, 1.f, 0.f);
	PlayerStateData.VelocityZ = PlayerStateData.Velocity.Z;
	PlayerStateData.GroundSpeed = PlayerStateData.Velocity2D.Length();
	PlayerStateData.Acceleration = OwnerPlayer->GetCharacterMovement()->GetCurrentAcceleration();
	PlayerStateData.Acceleration2D = PlayerStateData.Acceleration * FVector(1.f, 1.f, 0.f);
	PlayerStateData.WorldRotation = OwnerPlayer->GetActorRotation();
	PlayerStateData.VelocityAngle = CalculateDirection(PlayerStateData.Velocity, PlayerStateData.WorldRotation);
	PlayerStateData.AccelerationAngle = CalculateDirection(PlayerStateData.Acceleration, PlayerStateData.WorldRotation);
	PlayerStateData.IsAcceleration = !FMath::IsNearlyEqual(PlayerStateData.Acceleration2D.Length(), 0, 0.001);
	PlayerStateData.IsCrouch = OwnerPlayer->bIsCrouched;
	PlayerStateData.IsFalling = PlayerMovement->IsFalling();
	PlayerStateData.IsFlying = PlayerMovement->IsFlying();

	PlayerStateData.ShouldMove = PlayerStateData.GroundSpeed > 3.f && !PlayerStateData.Acceleration.IsNearlyZero();

	if (!FMath::IsNearlyZero(PlayerStateData.VelocityZ) && PlayerStateData.IsFalling)
	{
		PlayerStateData.IsJump = true;
	}
}
