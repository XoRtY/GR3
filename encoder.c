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

int main() {

  printf("cenas");

  SimpleSyntax_t* simple;
  simple = calloc(1, sizeof(SimpleSyntax_t));
  simple->present = SimpleSyntax_PR_integer_value;
  simple->choice.integer_value = 1;

  ObjectSyntax_t* object_syntax;
  object_syntax = calloc(1, sizeof(ObjectSyntax_t));
  object_syntax->present = ObjectSyntax_PR_simple;
  object_syntax->choice.simple = *simple;

  ObjectName_t* object_name;
  object_name = calloc(1, sizeof(ObjectName_t));
  object_name->buf = "ip";
  object_name->size = 2;

  VarBind_t* var_bind;
  var_bind = calloc(1, sizeof(VarBind_t));
  var_bind->name = *object_name;
  var_bind->choice.present = choice_PR_value;
  var_bind->choice.choice.value = *object_syntax;

  VarBindList_t* varlist;
  varlist = calloc(1, sizeof(VarBindList_t));
  int r = ASN_SEQUENCE_ADD(&varlist->list, var_bind);

  SetRequest_PDU_t* setRequestPDU;
  setRequestPDU = calloc(1, sizeof(GetRequest_PDU_t));
  setRequestPDU->request_id = 1;
  setRequestPDU->error_index = 0;
  setRequestPDU->error_status = 0;
  setRequestPDU->variable_bindings = *varlist;

  PDUs_t *pdus;
  pdus = calloc(1, sizeof(PDUs_t));
  pdus->present = PDUs_PR_set_request;
  pdus->choice.set_request = *setRequestPDU;

  uint8_t buffer[1024];
  size_t buffer_size = sizeof(buffer);

  asn_enc_rval_t ret = asn_encode_to_buffer(0, ATS_BER,&asn_DEF_PDUs, pdus, buffer, buffer_size);

  ANY_t* data;
  data = calloc(1, sizeof(ANY_t));
  data->buf = buffer;
  data->size = ret.encoded;

  OCTET_STRING_t community;
  community.buf = strdup("public");
  community.size = 6;
  long version = 3;

  Message_t* message;
  message = calloc(1, sizeof(Message_t));
  message->version = version;
  message->community = community;
  message->data = *data;

  uint8_t buffer_final[1024];
  size_t buffer_final_size = sizeof(buffer_final);

  asn_enc_rval_t retf = asn_encode_to_buffer(0, ATS_BER,&asn_DEF_Message, message, buffer_final, buffer_final_size);

  xer_fprint(stdout, &asn_DEF_Message, message);

}
