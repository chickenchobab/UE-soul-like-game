// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulTypes/SoulCountDownAction.h"

void FSoulCountDownAction::UpdateOperation(FLatentResponse& Response)
{
  if (bNeedToCancel)
  {
    CountDownOutput = ESoulCountDownActionOutput::Cancelled;

    Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

    return;
  }

  if (ElapsedTimeSinceStart >= TotalCountDownTime)
  {
    CountDownOutput = ESoulCountDownActionOutput::Completed;

    Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

    return;
  }

  if (ElapsedInterval < UpdateInterval)
  {
    ElapsedInterval += Response.ElapsedTime();
  }
  else
  {
    ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

    OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

    CountDownOutput = ESoulCountDownActionOutput::Updated;

    Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

    ElapsedInterval = 0.f;
  }
}

void FSoulCountDownAction::CancelAction()
{
  bNeedToCancel = true;
}