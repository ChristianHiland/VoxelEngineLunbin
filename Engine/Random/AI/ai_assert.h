/** @file ai_assert.h
 *  @brief Declares the assimp-specific assertion handler.
 */

#pragma once
#ifndef AI_ASSERT_H_INC
#define AI_ASSERT_H_INC

#include "defs.h"

#if defined(ASSIMP_BUILD_DEBUG)

namespace Assimp {

/// @brief Assert violation behavior can be customized: see AssertHandler.h.
/// @param failedExpression     The expression to validate.
/// @param file                 The file location
/// @param line                 The line number
ASSIMP_API void aiAssertViolation(const char* failedExpression, const char* file, int line);

}
#endif

// Define assertion resolinig
#if defined(ASSIMP_BUILD_DEBUG)
#   define ai_assert(expression) (void)((!!(expression)) || (Assimp::aiAssertViolation(#expression, __FILE__, __LINE__), 0))
#   define ai_assert_entry() ai_assert(false)
#else
#   define  ai_assert(expression)
#   define  ai_assert_entry()
#endif // ASSIMP_BUILD_DEBUG

#endif // AI_ASSERT_H_INC
