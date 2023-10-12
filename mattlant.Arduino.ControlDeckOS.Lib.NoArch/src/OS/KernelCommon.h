#pragma once
#ifndef EMB_KERNEL_COMMON_H
#define EMB_KERNEL_COMMON_H

#include <stdint.h>

#define EMK_HIGH_PRECISION_SCHEDULING 0
#define EMK_DEFAULT_MAX_EXEC_TIME 50
#define EMK_DEFAULT_MIN_EXEC_TIME 1


struct TaskExecutionResult
{
	enum ResultStatus
	{
		COMPLETE,
		RESUME,
		RESCHEDULE,
		ADD_TASK,
		DISABLE,
		DELETE,
		ERROR,
		ERROR_DISABLED
	} result;

	union
	{
		struct
		{
			uint8_t stage;
			unsigned int ticks;
		} resume;

		struct
		{
			unsigned int ticks;
		} reschedule;

		struct
		{
			void* task;
			bool immediate;
		} new_task;

		struct
		{
			uint8_t code;
			const char* message; //message is optional. Use caution - must be in scope when read by kernel.
		} error;
	} data; //TODO: Remove!

	static TaskExecutionResult Resume(int stage, int in_ticks)
	{
		TaskExecutionResult result;
		result.result = TaskExecutionResult::ResultStatus::RESUME;
		result.data.resume.stage = stage;
		result.data.resume.ticks = in_ticks;
		return result;
	}
};

struct TaskEvent
{
	// Can be either the event producer, or the consumer
	uint16_t owner_id;

	enum EventType
	{
		DATA_READY,
		DEVICE,
		INTERRUPT_HW,
		INTERRUPT_SW,
	} type;

	union
	{
		// Union to hold event-specific data
		struct
		{
			uint8_t* data; // Pointer to the data buffer
			uint16_t length; // Length of the data
		} dataReady;

		struct
		{
			uint8_t channel;
			uint8_t device_id;
			uint8_t event_id;
		} device_event;

		struct
		{
			uint8_t id;
		} interrupt;

		// Additional data fields for other event types can go here
	} eventData;
};

typedef TaskExecutionResult (*TaskFunc)();
typedef TaskExecutionResult (*TaskIntParamFunc)(int);
typedef TaskExecutionResult (*TaskCharParamFunc)(const char*);
typedef TaskExecutionResult (*TaskResumeFunc)(uint8_t);

#define TASK_RESULT_COMPLETE TaskExecutionResult{TaskExecutionResult::COMPLETE}


#define STAGED_PROCESS_BEGIN(stage_variable)    \
    TaskExecutionResult result;                 \
    result.result = TaskExecutionResult::ResultStatus::COMPLETE; \
    switch (stage_variable) {

#define STAGE(N)                              \
    case N:
#define PROCESS_COMPLETE()                    \
    result.result = TaskExecutionResult::ResultStatus::COMPLETE; \
    return result;

#define RESUME_AT_STAGE_IN_TICKS(N, in_ticks)           \
    result.result = TaskExecutionResult::ResultStatus::RESUME; \
    result.data.resume.stage = N;              \
    result.data.resume.ticks = in_ticks;          \
    return result;

#define STAGED_PROCESS_END()                    \
    default:                                  \
        result.result = TaskExecutionResult::ResultStatus::ERROR; \
        result.data.error.code = 0xFF;         \
        return result;                         \
    }


#define LOOP_PROCESS_BEGIN(init_action, first_stage) \
        if (resume_stage == 0) {                                      \
			init_action; \
            return TaskExecutionResult::Resume(first_stage, 0);  \
        }

#define FOR_PROCESS_STAGE(condition_expr, iter_expr, scope_block) \
    if (resume_stage == 1) {                             \
        if (condition_expr) {                               \
			scope_block; \
			iter_expr;\
            return TaskExecutionResult::Resume(1, 0);     \
        }                                                     \
    } 
#define WHILE_PROCESS_STAGE(condition_expr, scope_block) \
    if (resume_stage == 1) {                             \
        if (condition_expr) {                               \
			scope_block;                                          \
            return TaskExecutionResult::Resume(1, 0);     \
        }                                                     \
    }
#define DO_WHILE_PROCESS_STAGE(scope_block, condition_expr) \
    if (resume_stage == 1) {                             \
        scope_block;                                          \
        if (condition_expr) {                               \
            return TaskExecutionResult::Resume(1, 0);     \
        }                                                     \
    }
#define LOOP_PROCESS_END(complete_action)                          \
	complete_action; \
    return TASK_RESULT_COMPLETE;


//#define TASK_RESULT_RESUME(at_stage, in_ticks) \
//	TaskExecutionResult{result=TaskExecutionResult::COMPLETE}

//result.data.error.message = "Undefined resume stage"; \

#endif
