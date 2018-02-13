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

int main(int argc, char const *argv[]) {

  FILE *fp;
  uint8_t * buf;
  size_t buf_size;
  puts("Linha1");
  fp = fopen("encoded.bin", "rb");

  fseek(fp, 0, SEEK_END);
  buf_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buf = (uint8_t *)malloc(buf_size+1);
  puts("Linha2");
  fread(buf, buf_size, 1, fp);
  fclose(fp);

  Message_t *message = 0;
  asn_dec_rval_t rval = asn_decode(0, ATS_BER, &asn_DEF_Message, (void **)&message, buf, buf_size);

  PDUs_t* pdu = 0;

  asn_dec_rval_t rvalf = asn_decode(0, ATS_BER, &asn_DEF_PDUs,(void **)&pdu, message->data.buf, message->data.size);

  VarBindList_t var_bindings = pdu->choice.set_request.variable_bindings;
  int var_list_size = var_bindings.list.count;
  VarBind_t* var_bind = var_bindings.list.array[0];

  ObjectName_t object_name = var_bind->name;

  ObjectSyntax_t object_syntax = var_bind->choice.choice.value;

  SimpleSyntax_t simple = object_syntax.choice.simple;
  puts("Linha3");
  PDUs_PR requestType = pdu->present;
  char* snmpC;
  long version = message->version;
  char* community = message->community.buf;
  if(requestType == PDUs_PR_get_request){
    snmpC = "get";
  }
  else 
    if(requestType == PDUs_PR_get_bulk_request){
      snmpC = "bulkget";
    }
    else
      if(requestType == PDUs_PR_get_next_request){
        snmpC = "getnext";
      }
      else
        if(requestType == PDUs_PR_set_request){
          snmpC = "set";
        }
  puts("Linha4");
  int ipsize = object_name.size;
  char* ip = malloc(sizeof(char) * (ipsize + ipsize));
  int i = 0; int j = 0;
  while(i < ipsize){
    ip[j] = object_name.buf[i];
    j++;
    ip[j] = '.';
    j++;
  }
  ip[j] = '\0';
  puts("Linha5")
  printf("snmp%s -v %ld -c %s %s", snmpC, version, community, ip);

  free(ip);

  
  //FILE *out;
  //out = fopen("decoded.txt", "w");
  //fprintf(out, "%ld\n%s\n%ld\n%ld\n%s\n", simple.choice.integer_value, object_name.buf, pdu->choice.set_request.request_id, message->version, message->community.buf);

}
