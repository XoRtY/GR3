#include <stdlib.h>
#include <stdio.h>
#include "OCTET_STRING.h"
#include "SimpleSyntax.h"
#include "ObjectSyntax.h"
#include "ObjectName.h"
#include "VarBind.h"
#include "VarBindList.h"
#include "SetRequest-PDU.h"
#include "GetRequest-PDU.h"
#include "PDUs.h"
#include "ANY.h"
#include "Message.h"
#include "creates.h"

//Create empty simple syntax
SimpleSyntax_t * SimpleSyntax(){
  SimpleSyntax_t *simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_NOTHING;
  return simple;
}

//Create simple syntax with Integer
SimpleSyntax_t * IntSimpleSyntax(long integer_value){
  SimpleSyntax_t *simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_integer_value;
  simple->choice.integer_value = integer_value;
  return simple;
}

//Create simple syntax with octet 
SimpleSyntax_t * OctetSimpleSyntax(OCTET_STRING_t string_value){
  SimpleSyntax_t *simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_string_value;
  simple->choice.string_value = string_value;
  return simple;
}

//Create simple syntax with object
SimpleSyntax_t * ObjectSimpleSyntax(OBJECT_IDENTIFIER_t objectID_value){
  SimpleSyntax_t *simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_objectID_value;
  simple->choice.objectID_value = objectID_value;
  return simple;
}

//Create empty app syntax
ApplicationSyntax_t * ApplicationSyntax(){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_NOTHING;
  return application;
}

//Create IP app syntax
ApplicationSyntax_t * IPApplicationSyntax(IpAddress_t ipAddress_value){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_ipAddress_value;
  application->choice.ipAddress_value = ipAddress_value;
  return application;
}

//Create counter32 app syntax
ApplicationSyntax_t * Counter32ApplicationSyntax(Counter32_t counter_value){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_counter_value;
  application->choice.counter_value = counter_value;
  return application;
}

//Create counter 64 app syntax
ApplicationSyntax_t * Counter64ApplicationSyntax(Counter64_t big_counter_value){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_big_counter_value;
  application->choice.big_counter_value = big_counter_value;
  return application;
}

//Create timestick app syntax
ApplicationSyntax_t * TimeticksApplicationSyntax(TimeTicks_t timeticks_value){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_timeticks_value;
  application->choice.timeticks_value = timeticks_value;
  return application;
}

//Create opaque app syntax
ApplicationSyntax_t * OpaqueApplicationSyntax(Opaque_t arbitrary_value){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_arbitrary_value;
  application->choice.arbitrary_value = arbitrary_value;
  return application;
}

//Create unsigned app syntax
ApplicationSyntax_t * UnsignedApplicationSyntax(Unsigned32_t unsigned_integer_value){
  ApplicationSyntax_t *application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_unsigned_integer_value;
  application->choice.unsigned_integer_value = unsigned_integer_value;
  return application;
}


SetRequest_PDU_t * setReq (int request_id, VarBindList_t * varlist){
    SetRequest_PDU_t* setRequestPDU;
    setRequestPDU = calloc(1, sizeof(SetRequest_PDU_t));
    setRequestPDU->request_id = atoi(argv[3]); // 1
    setRequestPDU->error_index = 0;
    setRequestPDU->error_status = 0;
    setRequestPDU->variable_bindings = *varlist;
}