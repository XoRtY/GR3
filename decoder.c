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
#include <mxml.h>

int main(int argc, char const *argv[]) {

  FILE *fp;
  mxml_node_t *tree;

  fp = fopen("encoded.xml", "r");
  tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);

  Message_t *message = 0;
  uint8_t buffer_final[1024];
  size_t buffer_final_size = sizeof(buffer_final);

  asn_dec_rval_t rval = asn_decode(0, ATS_BER, &asn_DEF_Message, (void **)&message, buffer_final, buffer_final_size);

  PDUs_t* pdu = 0;

  asn_dec_rval_t rvalf = asn_decode(0, ATS_BER, &asn_DEF_PDUs,(void **)&pdu, message->data.buf, message->data.size);

  VarBindList_t var_bindings = pdu->choice.set_request.variable_bindings;
  int var_list_size = var_bindings.list.count;
  VarBind_t* var_bind = var_bindings.list.array[0];

  xer_fprint(stdout, &asn_DEF_PDUs, pdu);

  fclose(fp);

}
