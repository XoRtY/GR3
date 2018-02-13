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
#include "stdbool.h"
#include "asn_application.h"

/**uint8_t *ipToUint (char * ip){
  uint8_t ipU[4];
  int i = 0;
  char * tmp;
  tmp = strtok (ip,".");
  while (tmp != NULL){
    ipU[i] = atoi(tmp);
    tmp = strtok (NULL, ".");
    i++;
  }
  return *ipU;
}*/

//Create empty simple syntax
SimpleSyntax_t * SimpleSyntax(){
  SimpleSyntax_t * simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_NOTHING;
  return simple;
}

//Create simple syntax with Integer
SimpleSyntax_t * IntSimpleSyntax(long int_value){
  SimpleSyntax_t * simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_integer_value;
  simple->choice.integer_value = int_value;
  return simple;
}

//Create simple syntax with octet 
SimpleSyntax_t * OctetSimpleSyntax(OCTET_STRING_t string_value){
  SimpleSyntax_t * simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_string_value;
  simple->choice.string_value = string_value;
  return simple;
}

//Create simple syntax with object
SimpleSyntax_t * ObjectSimpleSyntax(OBJECT_IDENTIFIER_t objectID_value){
  SimpleSyntax_t * simple;
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
  ApplicationSyntax_t * application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_ipAddress_value;
  application->choice.ipAddress_value = ipAddress_value;
  return application;
}

//Create counter32 app syntax
ApplicationSyntax_t * Counter32ApplicationSyntax(Counter32_t counter_value){
  ApplicationSyntax_t * application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_counter_value;
  application->choice.counter_value = counter_value;
  return application;
}

//Create counter 64 app syntax
ApplicationSyntax_t * Counter64ApplicationSyntax(Counter64_t big_counter_value){
  ApplicationSyntax_t * application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_big_counter_value;
  application->choice.big_counter_value = big_counter_value;
  return application;
}

//Create timestick app syntax
ApplicationSyntax_t * TimeticksApplicationSyntax(TimeTicks_t timeticks_value){
  ApplicationSyntax_t * application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_timeticks_value;
  application->choice.timeticks_value = timeticks_value;
  return application;
}

//Create opaque app syntax
ApplicationSyntax_t * OpaqueApplicationSyntax(Opaque_t arbitrary_value){
  ApplicationSyntax_t * application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_arbitrary_value;
  application->choice.arbitrary_value = arbitrary_value;
  return application;
}

//Create unsigned app syntax
ApplicationSyntax_t * UnsignedApplicationSyntax(Unsigned32_t unsigned_integer_value){
  ApplicationSyntax_t * application;
  application = calloc(1, sizeof(ApplicationSyntax_t));
  application->present = ApplicationSyntax_PR_unsigned_integer_value;
  application->choice.unsigned_integer_value = unsigned_integer_value;
  return application;
}

//Create empty object syntax
ObjectSyntax_t * ObjectSyntax(SimpleSyntax_t *simple){
  ObjectSyntax_t * object_syntax;
  object_syntax = calloc(1, sizeof(ObjectSyntax_t));
  object_syntax->present = ObjectSyntax_PR_simple;
  object_syntax->choice.simple = *simple;
  return object_syntax;
}

//Create app object syntax
ObjectSyntax_t * ObjectApplicationSyntax(ApplicationSyntax_t *application){
  ObjectSyntax_t * object_syntax;
  object_syntax = calloc(1, sizeof(ObjectSyntax_t));
  object_syntax->present = ObjectSyntax_PR_application_wide;
  object_syntax->choice.application_wide = *application;
  return object_syntax;
}

//Create Object name
ObjectName_t * ObjectName(uint8_t* name,size_t name_size){
  ObjectName_t * object_name;
  object_name = calloc(1, sizeof(ObjectName_t));
  object_name->buf = name;
  object_name->size = name_size;
  return object_name;
}

//Create var bind
VarBind_t * cVarBind(ObjectName_t *object_name, ObjectSyntax_t *object_syntax){
  VarBind_t * var_bind;
  var_bind = calloc(1, sizeof(VarBind_t));
  var_bind->name = *object_name;
  var_bind->choice.present = choice_PR_value;
  var_bind->choice.choice.value = *object_syntax;
  return var_bind;
}

//Create List var bind
VarBindList_t * ListVarBind(VarBind_t * var_bind){
  VarBindList_t * varlist;
  varlist = calloc(1, sizeof(VarBindList_t));
  int r = ASN_SEQUENCE_ADD(&varlist->list, var_bind);
  return varlist;
}

//Create PDU get Request
GetRequest_PDU_t * PDUGetRequest(int request_id, VarBindList_t* varlist){
  GetRequest_PDU_t * getRequestPDU;
  getRequestPDU = calloc(1, sizeof(GetRequest_PDU_t));
  getRequestPDU->request_id = request_id;
  getRequestPDU->error_index = 0;
  getRequestPDU->error_status = 0;
  getRequestPDU->variable_bindings = *varlist;
  return getRequestPDU;
}

//Create PDU get bulk Request
GetBulkRequest_PDU_t * PDUGetBulkRequest(int request_id, VarBindList_t* varlist){
  GetBulkRequest_PDU_t * getBulkRequestPDU;
  getBulkRequestPDU = calloc(1, sizeof(GetBulkRequest_PDU_t));
  getBulkRequestPDU->request_id = request_id;
  getBulkRequestPDU->non_repeaters = 0;
  getBulkRequestPDU->max_repetitions = 0;
  getBulkRequestPDU->variable_bindings = *varlist;
  return getBulkRequestPDU;
}

//Create PDU get next request
GetNextRequest_PDU_t * PDUGetNextRequest(int request_id, VarBindList_t* varlist){
  GetNextRequest_PDU_t * getNextRequestPDU;
  getNextRequestPDU = calloc(1, sizeof(GetNextRequest_PDU_t));
  getNextRequestPDU->request_id = request_id;
  getNextRequestPDU->error_index = 0;
  getNextRequestPDU->error_status = 0;
  getNextRequestPDU->variable_bindings = *varlist;
  return getNextRequestPDU;
}

//Create PDU response
Response_PDU_t * PDUResponse(int request_id, VarBindList_t* varlist){
  Response_PDU_t * responsePDU;
  responsePDU = calloc(1, sizeof(Response_PDU_t));
  responsePDU->request_id = request_id;
  responsePDU->error_index = 0;
  responsePDU->error_status = 0;
  responsePDU->variable_bindings = *varlist;
  return responsePDU;
}

//Create PDU set request
SetRequest_PDU_t * PDUSetRequest(int request_id, VarBindList_t* varlist){
  SetRequest_PDU_t * setRequestPDU;
  setRequestPDU = calloc(1, sizeof(SetRequest_PDU_t));
  setRequestPDU->request_id = request_id;
  setRequestPDU->error_index = 0;
  setRequestPDU->error_status = 0;
  setRequestPDU->variable_bindings = *varlist;
  return setRequestPDU;
}

//Create PDU Inform Request
InformRequest_PDU_t * PDUInformRequest(int request_id, VarBindList_t* varlist){
  InformRequest_PDU_t * informRequestPDU;
  informRequestPDU = calloc(1, sizeof(InformRequest_PDU_t));
  informRequestPDU->request_id = request_id;
  informRequestPDU->error_index = 0;
  informRequestPDU->error_status = 0;
  informRequestPDU->variable_bindings = *varlist;
  return informRequestPDU;
}

//Create PDU trap
SNMPv2_Trap_PDU_t * PDUTrap(int request_id, VarBindList_t* varlist){
  SNMPv2_Trap_PDU_t * snmpV2_trapPDU;
  snmpV2_trapPDU = calloc(1, sizeof(SNMPv2_Trap_PDU_t));
  snmpV2_trapPDU->request_id = request_id;
  snmpV2_trapPDU->error_index = 0;
  snmpV2_trapPDU->error_status = 0;
  snmpV2_trapPDU->variable_bindings = *varlist;
  return snmpV2_trapPDU;
}

//Create PDU report
Report_PDU_t * PDUReport(int request_id, VarBindList_t* varlist){
  Report_PDU_t * reportPDU;
  reportPDU = calloc(1, sizeof(Report_PDU_t));
  reportPDU->request_id = request_id;
  reportPDU->error_index = 0;
  reportPDU->error_status = 0;
  reportPDU->variable_bindings = *varlist;
  return reportPDU;
}

//Create PDU get
PDUs_t * PDUget(GetRequest_PDU_t* get_requestPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_get_request;
  pdu_t->choice.get_request = *get_requestPDU;
  return pdu_t;
}

//Create PDU get next
PDUs_t * PDUgetnext(GetNextRequest_PDU_t* get_next_requestPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_get_next_request;
  pdu_t->choice.get_next_request = *get_next_requestPDU;
  return pdu_t;
}

//Create PDU get bulk
PDUs_t * PDUgetbulk(GetBulkRequest_PDU_t* get_bulk_requestPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_get_bulk_request;
  pdu_t->choice.get_bulk_request = *get_bulk_requestPDU;
  return pdu_t;
}

//Create PDU response
PDUs_t * PDUresponse(Response_PDU_t* responsePDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_response;
  pdu_t->choice.response = *responsePDU;
  return pdu_t;
}

//Create PDU set
PDUs_t * PDUset(SetRequest_PDU_t* set_requestPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_set_request;
  pdu_t->choice.set_request = *set_requestPDU;
  return pdu_t;
}

//Create PDU inform
PDUs_t * PDUinform(InformRequest_PDU_t* informRequestPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_inform_request;
  pdu_t->choice.inform_request = *informRequestPDU;
  return pdu_t;
}

//Create PDU trap
PDUs_t * PDUtrap(SNMPv2_Trap_PDU_t* snmpV2_trapPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_snmpV2_trap;
  pdu_t->choice.snmpV2_trap = *snmpV2_trapPDU;
  return pdu_t;
}

//Create PDU report
PDUs_t * PDUreport(Report_PDU_t* reportPDU){
  PDUs_t * pdu_t;
  pdu_t = calloc(1, sizeof(PDUs_t));
  pdu_t->present = PDUs_PR_report;
  pdu_t->choice.report = *reportPDU;
  return pdu_t;
}

//encode (ALL)
asn_enc_rval_t encode(uint8_t *buffer, size_t buffer_size, PDUs_t *pdu_t){
  return (asn_encode_to_buffer(0, ATS_BER, &asn_DEF_PDUs, pdu_t, buffer, buffer_size) );
}

//Create ANY
ANY_t * cANY(uint8_t *buffer, asn_enc_rval_t r){
  ANY_t * data;
  data = calloc(1, sizeof(ANY_t));
  data->buf = buffer;
  data->size = r.encoded;
  return data;
}

//Create Message
Message_t * cMessage(long version, OCTET_STRING_t community, ANY_t* data){  
  Message_t * message;
  message = calloc(1, sizeof(Message_t));
  message->version = version;
  message->community = community;
  message->data = *data;
  return message;
}

asn_enc_rval_t EndEncode(uint8_t *endBuffer, size_t endBuffer_size, Message_t* message){
  return asn_encode_to_buffer(0, ATS_BER, &asn_DEF_Message, message, endBuffer, endBuffer_size);
}


int main(int argc, char const *argv[]) {
  SimpleSyntax_t* simpleSyntax;
  ObjectSyntax_t* objectSyntax;
  ObjectName_t * objectName;
  VarBind_t* varBind;
  VarBindList_t* varList;
  PDUs_t* pdu_t;
  ApplicationSyntax_t* appSyntax;
  
  uint8_t buffer[2048];
  size_t buffer_size = sizeof(buffer);

  if(argc <= 1){
    printf("Error, command not supported.(snmptrapd, snmpinform and snmpreport not working) Available command example: |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n");
    return -1;
  }


  if (strcmp(argv[1],"snmpget")==0){
    if(argc != 8){
        printf("Error, command not supported. Available command example: |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n");
        return -1;
    }
    simpleSyntax = IntSimpleSyntax( 0);
    objectSyntax = ObjectSyntax( simpleSyntax);

    char* ip = argv[6];
      uint8_t ipU[4];
      int i = 0;
      char * tmp;
        tmp = strtok (ip,".");
        while (tmp != NULL){
          ipU[i] = atoi(tmp);
          tmp = strtok (NULL, ".");
          i++;
        }
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = cVarBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    GetRequest_PDU_t* getRequest = PDUGetRequest( 1, varList);
    pdu_t = PDUget( getRequest);
  }
  else if (strcmp(argv[1],"snmpbulkget")==0){
    if(argc != 8){
        printf("Error, command not supported. Available command example: |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n");
        return -1;
    }
    simpleSyntax = IntSimpleSyntax( 0);
    objectSyntax = ObjectSyntax( simpleSyntax);

    char* ip = argv[6];
      uint8_t ipU[4];
      int i = 0;
      char * tmp;
        tmp = strtok (ip,".");
        while (tmp != NULL){
          ipU[i] = atoi(tmp);
          tmp = strtok (NULL, ".");
          i++;
        }
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = cVarBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    GetBulkRequest_PDU_t* getBulkRequest = PDUGetBulkRequest( 1, varList);
    pdu_t = PDUgetbulk( getBulkRequest);
  }
  else if (strcmp(argv[1],"snmpgetnext")==0){
    if(argc != 8){
        printf("Error, command not supported. Available command example: |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n");
        return -1;
    }
    simpleSyntax = IntSimpleSyntax( 0);
    objectSyntax = ObjectSyntax( simpleSyntax);

    char* ip = argv[6];
      uint8_t ipU[4];
      int i = 0;
      char * tmp;
        tmp = strtok (ip,".");
        while (tmp != NULL){
          ipU[i] = atoi(tmp);
          tmp = strtok (NULL, ".");
          i++;
        }
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = cVarBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    GetNextRequest_PDU_t* getNextRequest = PDUGetNextRequest( 1, varList);
    pdu_t = PDUgetnext( getNextRequest);
  }
  else if (strcmp(argv[1],"snmpgetresponse")==0){
    /*if(argc != 8){
        printf("Error, command not supported.\n
                Available command example:\n
                |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n")
    }*/
    printf("Under work");
    return -1;
  }
  else if (strcmp(argv[1],"snmpset")==0){
    if(argc != 10){
        printf("Error, command not supported. Available command example: |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n");
        return -1;
    }
    bool simpleB = false;
    if (strcmp(argv[8], "i")==0){
      simpleSyntax = IntSimpleSyntax(atoi(argv[9]));
      simpleB = true;
    }
    else if (strcmp(argv[8],"t")==0){
      appSyntax = TimeticksApplicationSyntax(atoi(argv[9]));
    }
    else if (strcmp(argv[8],"u")==0){
      appSyntax = UnsignedApplicationSyntax(atoi(argv[9]));
    }
    else{
      printf ("Command not supported, try i, u or t");
      return -1;
    }
    if(simpleB == true){
      objectSyntax = ObjectSyntax(simpleSyntax);
    }
    else{
      objectSyntax = ObjectApplicationSyntax(appSyntax);
    }
    char* ip = argv[6];
      uint8_t ipU[4];
      int i = 0;
      char * tmp;
        tmp = strtok (ip,".");
        while (tmp != NULL){
          ipU[i] = atoi(tmp);
          tmp = strtok (NULL, ".");
          i++;
        }
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = cVarBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    SetRequest_PDU_t* setRequest = PDUSetRequest(1, varList);
    pdu_t = PDUset( setRequest);
  }
  else{
    printf("Error, command not supported.(snmptrapd, snmpinform and snmpreport not working) Available command example: |snmpCommand| -v |versionNumber| -c |comString| |IP| |OID|\n");
    return -1;
  }

  uint8_t encodeRes[2048];
  size_t resSize = sizeof( encodeRes);
  asn_enc_rval_t value = encode( encodeRes, resSize, pdu_t);
  printf("First encodinh done\n");

  ANY_t* data = cANY(encodeRes,value);
  long v = atoi(argv[3]);
  OCTET_STRING_t oString;
  oString.buf = strdup(argv[5]);
  oString.size = sizeof(oString.buf);
  Message_t * message = cMessage(v, oString,data);

  uint8_t encodeResFinal[2048];
  size_t ResFinalSize = sizeof(encodeResFinal);
  asn_enc_rval_t valueFinal = EndEncode(encodeResFinal, ResFinalSize, message);
  printf("Final encodinh done\n");


  FILE *fp = fopen("encodedPDU.binary","w");
  if(!fp){
    perror("File not found");
    return -1;
  }
  else{
    fwrite(encodeResFinal, valueFinal.encoded , 1, fp);
    printf("Success\n");

  }
  fclose(fp);

  FILE * fpDebug;
  fpDebug = fopen("debugFile.xml","w");
  if(fpDebug == NULL){
    perror("debugFile.xml errosr");
    return -1;
  }

  xer_fprint(fpDebug, &asn_DEF_Message, message);
  printf("Debug success\n");
  fclose(fpDebug);

  return 0;
}
