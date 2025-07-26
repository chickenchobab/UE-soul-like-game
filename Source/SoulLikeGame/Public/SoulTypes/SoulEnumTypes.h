#pragma once

UENUM(BlueprintType)
enum class ESoulConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class ESoulValidType : uint8
{
  Valid,
  InValid
};

UENUM()
enum class ESoulSuccessType : uint8
{
  Successful,
  Failed
};