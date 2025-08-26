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

UENUM()
enum class ESoulCountDownActionInput : uint8
{
  Start,
  Cancel
};

UENUM()
enum class ESoulCountDownActionOutput : uint8
{
  Updated,
  Completed,
  Cancelled
};

UENUM(BlueprintType)
enum class ESoulGameDifficulty : uint8
{
  Easy,
  Normal,
  Hard,
  VeryHard
};

UENUM(BlueprintType)
enum class ESoulInputMode : uint8
{
  GameOnly,
  UIOnly
};