// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/********************************************************************
 * COPYRIGHT: 
 * Copyright (c) 2004-2010, International Business Machines Corporation and
 * others. All Rights Reserved.
 ********************************************************************/

/* Created by grhoten 03/17/2004 */

/* Base class for data driven tests */

#ifndef U_TESTFW_TESTLOG
#define U_TESTFW_TESTLOG

#include "unicode/errorcode.h"
#include "unicode/unistr.h"
#include "unicode/testtype.h"

/** Facilitates internal logging of data driven test service 
 *  It would be interesting to develop this into a full      
 *  fledged control system as in Java.                       
 */
class T_CTEST_EXPORT_API TestLog {
public:
    virtual ~TestLog();
    virtual void errln( const UnicodeString &message ) = 0;
    virtual void logln( const UnicodeString &message ) = 0;
    virtual void dataerrln( const UnicodeString &message ) = 0;
    virtual const char* getTestDataPath(UErrorCode& err) = 0;
};

class T_CTEST_EXPORT_API IcuTestErrorCode : public ErrorCode {
public:
    IcuTestErrorCode(TestLog &callingTestClass, const char *callingTestName)
            : testClass(callingTestClass), testName(callingTestName), scopeMessage() {}
    virtual ~IcuTestErrorCode();

    // Returns TRUE if isFailure().
    UBool errIfFailureAndReset();
    __attribute__((format(printf, 2, 3)))
    UBool errIfFailureAndReset(const char *fmt, ...);
    UBool errDataIfFailureAndReset();
    __attribute__((format(printf, 2, 3)))
    UBool errDataIfFailureAndReset(const char *fmt, ...);
    UBool expectErrorAndReset(UErrorCode expectedError);
    __attribute__((format(printf, 3, 4)))
    UBool expectErrorAndReset(UErrorCode expectedError, const char *fmt, ...);

    /** Sets an additional message string to be appended to failure output. */
    void setScope(const char* message);
    void setScope(const UnicodeString& message);

protected:
    virtual void handleFailure() const override;

private:
    TestLog &testClass;
    const char *const testName;
    UnicodeString scopeMessage;

    void errlog(UBool dataErr, const UnicodeString& mainMessage, const char* extraMessage) const;
};

#endif
