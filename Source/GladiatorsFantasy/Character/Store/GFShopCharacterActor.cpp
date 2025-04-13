#include "Character/Store/GFShopCharacterActor.h"
#include "Server/GFBasePlayerState.h"
#include "DataTable/StoreSpawn/FGFStoreCharacterSpawnRow.h"
#include "Net/UnrealNetwork.h"


AGFShopCharacterActor::AGFShopCharacterActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	bReplicates = true;
}


void AGFShopCharacterActor::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (const AGFBasePlayerState* PS = PC->GetPlayerState<AGFBasePlayerState>())
		{
			SetupCharacterMesh(PS->GetCharacterBPName());
		}
	}
	
}

void AGFShopCharacterActor::OnRep_CharacterMesh()
{
	UE_LOG(LogTemp, Warning, TEXT("[CLIENT] OnRep_CharacterMesh called"));

	USkeletalMesh* Mesh = nullptr;

	if (ReplicatedMesh.IsValid())
	{
		Mesh = ReplicatedMesh.Get();
	}
	else if (!ReplicatedMesh.IsNull())
	{
		Mesh = ReplicatedMesh.LoadSynchronous(); // 반드시 동기 로드!
	}

	if (Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("[CLIENT] Applying Mesh: %s"), *Mesh->GetName());
		MeshComponent->SetSkeletalMesh(Mesh);
	}
}
void AGFShopCharacterActor::OnRep_CharacterAnim()
{
	UAnimSequence* Anim = nullptr;

	if (ReplicatedAnim.IsValid())
	{
		Anim = ReplicatedAnim.Get();
	}
	else if (!ReplicatedAnim.IsNull())
	{
		Anim = ReplicatedAnim.LoadSynchronous();
	}

	if (Anim)
	{
		MeshComponent->PlayAnimation(Anim, true);
	}
}

void AGFShopCharacterActor::SetupCharacterMesh(const FString& CharacterBPName)
{
	if (!StoreCharacterDataTable || !HasAuthority()) return;

	const FName RowName = FName(*CharacterBPName);
	const FGFStoreCharacterSpawnData* Row = StoreCharacterDataTable->FindRow<FGFStoreCharacterSpawnData>(RowName, TEXT("ShopCharMeshLookup"));

	if (!Row) return;

	// Replicated 변수에 설정 → 클라에서 OnRep 자동 호출됨
	ReplicatedMesh = Row->SkeletalMesh;
	ReplicatedAnim = Row->Animation;

	// 서버에서는 즉시 적용
	if (ReplicatedMesh.IsValid())
	{
		MeshComponent->SetSkeletalMesh(ReplicatedMesh.Get());
	}
	else if (!ReplicatedMesh.IsNull())
	{
		ReplicatedMesh.LoadSynchronous();
		MeshComponent->SetSkeletalMesh(ReplicatedMesh.Get());
	}

	if (ReplicatedAnim.IsValid())
	{
		MeshComponent->PlayAnimation(ReplicatedAnim.Get(), true);
	}
	else if (!ReplicatedAnim.IsNull())
	{
		ReplicatedAnim.LoadSynchronous();
		MeshComponent->PlayAnimation(ReplicatedAnim.Get(), true);
	}
}

void AGFShopCharacterActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGFShopCharacterActor, ReplicatedMesh);
	DOREPLIFETIME(AGFShopCharacterActor, ReplicatedAnim);
}



