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
#include "stdbool.h"

uint8_t ipToUint (char * ip){
  uint8_t ipU[4];
  int i = 0;
  char * tmp;
  tmp = strtok (ip,".");
  while (tmp != NULL){
    ipU[i] = atoi(tmp);
    tmp = strtok (NULL, ".");
    i++;
  }
  return ipU;
}

int main(int argc, char const *argv[]) {
  SimpleSyntax_t* simpleSyntax;
  ObjectSyntax_t* objectSyntax;
  ObjectName_t * objectName;
  VarBind_t* varBind;
  VarBindList_t* varList;
  PDUs_t* pdu_t;
  ApplicationSyntax_t* appSyntax;
  
  uint8_t buffer[1024];
  size_t buffer_size = sizeof(buffer);

  if(argc <= 1){
    printf("Error, command not supported.(snmptrapd, snmpinform and snmpreport not working)\n
            Available command example:\n
            \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n");
    return -1;
  }


  if (strcmp(argv[1],"snmpget")==0){
    if(argc != 8){
        printf("Error, command not supported.\n
                Available command example:\n
                \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n")
    }
    simpleSyntax = IntSimpleSyntax( 0);
    objectSyntax = ObjectSimpleSyntax( simpleSyntax);

    uint8_t ip[4] = ipToUint(argv[6]);
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = varBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    GetRequest_PDU_t* getRequest = PDUGetRequest( 1, varList);
    pdu_t = PDUget( getRequest);
  }
  else if (strcmp(argv[1],"snmpbulkget")==0){
    if(argc != 8){
        printf("Error, command not supported.\n
                Available command example:\n
                \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n")
    }
    simpleSyntax = IntSimpleSyntax( 0);
    objectSyntax = ObjectSimpleSyntax( simpleSyntax);

    uint8_t ip[4] = ipToUint(argv[6]);
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = varBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    GetBulkRequest_PDU_t* getBulkRequest = PDUGetBulkRequest( 1, varList);
    pdu_t = PDUgetbulk( getBulkRequest);
  }
  else if (strcmp(argv[1],"snmpgetnext")==0){
    if(argc != 8){
        printf("Error, command not supported.\n
                Available command example:\n
                \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n")
    }
    simpleSyntax = IntSimpleSyntax( 0);
    objectSyntax = ObjectSimpleSyntax( simpleSyntax);

    uint8_t ip[4] = ipToUint(argv[6]);
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = varBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    GetNextRequest_PDU_t* getNextRequest = PDUGetNextRequest( 1, varList);
    pdu_t = PDUgetnext( getNextRequest);
  }
  else if (strcmp(argv[1],"snmpgetresponse")==0){
    /*if(argc != 8){
        printf("Error, command not supported.\n
                Available command example:\n
                \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n")
    }*/
    printf("Under work");
    return -1;
  }
  else if (strcmp(argv[1],"snmpset")==0){
    if(argc != 10){
        printf("Error, command not supported.\n
                Available command example:\n
                \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n")
    }
    bool simpleB = false;
    if (strcmp(argv[8]m "i")==0){
      simple = IntSimpleSyntax(atoi(argv[9]));
      simpleB = true;
    }
    else if (strcmp(argv[8],"t")==0){
      appSyntax = TimetickApplicationSyntax(atoi(argv[9]));
    }
    else if (strcmp(argv[8],"u")==0){
      appSyntax = UnsignedApplicationSyntax(atoi(argv[9]));
    }
    else{
      printf ("Command not supported, try i, u or t");
    }
    if(simpleB == true){
      objectSyntax = ObjectSimpleSyntax(simple);
    }
    else{
      objectSyntax = ObjectApplicationSyntax(appSyntax);
    }
    uint8_t ip[4] = ipToUint(argv[6]);
    size_t ipSize = sizeof(ip);

    objectName = ObjectName( ip, ipSize);
    varBind = varBind( objectName, objectSyntax);
    varList = ListVarBind( varBind);
    SetRequest_PDU_t* setRequest = PDUSetRequest( varList);
    pdu_t = PDUset( setRequest);
  }
  else{
    printf("Error, command not supported.(snmptrapd, snmpinform and snmpreport not working)\n
            Available command example:\n
            \"snmpCommand\" -v \"versionNumber\" -c \"comString\" \"IP\" \"OID\"\n");
    return -1;
  }

  uint8_t encodeRes[1024];
  size_t resSize = sizeof( encodeRes);
  asn_enc_rval_t value = encode( encodeRes, resSize, pdu_t);
  printf("First encodinh done\n");

  ANY_t* data = ANY(encodeRes,value);
  long v = atoi(argv[3]);
  OCTET_STRING oString;
  oString.buf = strdup(argv[5]);
  oString.size = sizeof(oString.buf);
  Message_t * message = Message(v, oString ,data);

  uint8_t encodeResFinal[1024];
  size_t ResFinalSize = sizeof(encodeResFinal);
  asn_enc_rval_t valueFinal = EndEncode(encodeResFinal, ResFinalSize, message);
  printf("Final encodinh done\n");


  FILE *fp = fopen("encodedPDU.bin","w");
  if(!fp){
    perror("File not found");
    return -1;
  }
  else{
    fwrite(encodeResFinal, value2.encoded , 1, fp);
    printf("Success\n");

  }
  fclose(fp);

  File * fpDebug;
  fpDebug = fopen("debugFile.xml","w");
  if(spDebug == NULL){
    perror("debugFile.xml errosr");
    return -1;
  }

  xer_fprint(fpDebug, &asn_DEF_Message, message);
  printf("Debug success\n");
  fclose(fpDebug);

  return 0;
}
