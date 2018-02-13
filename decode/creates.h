#ifndef CREATES_H   /* Include guard */
#define CREATES_H

SimpleSyntax_t * SimpleSyntax();
SimpleSyntax_t * IntSimpleSyntax(long);
SimpleSyntax_t * OctetSimpleSyntax(OCTET_STRING_t);
SimpleSyntax_t * ObjectSimpleSyntax(OBJECT_IDENTIFIER_t);
ApplicationSyntax_t * ApplicationSyntax();
ApplicationSyntax_t * IPApplicationSyntax(IpAddress_t);
ApplicationSyntax_t * Counter32ApplicationSyntax(Counter32_t);
ApplicationSyntax_t * Counter64ApplicationSyntax(Counter64_t);
ApplicationSyntax_t * TimeticksApplicationSyntax(TimeTicks_t);
ApplicationSyntax_t * OpaqueApplicationSyntax(Opaque_t);
ApplicationSyntax_t * UnsignedApplicationSyntax(Unsigned32_t);
ObjectSyntax_t * ObjectSyntax(SimpleSyntax_t *);
ObjectSyntax_t * ObjectApplicationSyntax(ApplicationSyntax_t *);
ObjectName_t * ObjectName(uint8_t*, size_t);
VarBind_t * VarBind(ObjectName_t *, ObjectSyntax_t *);
VarBindList_t * ListVarBind(VarBind_t *);
GetRequest_PDU_t * PDUGetRequest(int, VarBindList_t*);
GetBulkRequest_PDU_t * PDUGetBulkRequest(int, VarBindList_t *);
GetNextRequest_PDU_t * PDUGetNextRequest(int, VarBindList_t *);
Response_PDU_t * PDUResponse(int, VarBindList_t *);
SetRequest_PDU_t * PDUSetRequest(int, VarBindList_t *);
InformRequest_PDU_t * PDUInformRequest(int, VarBindList_t *);
SNMPv2_Trap_PDU_t * PDUTrap(int, VarBindList_t *);
Report_PDU_t * PDUReport(int, VarBindList_t *);
PDUs_t * PDUget(GetRequest_PDU_t *);
PDUs_t * PDUgetnext(GetNextRequest_PDU_ t *);
PDUs_t * PDUgetbulk(GetBulkRequest_PDU_t *);
PDUs_t * PDUresponse(Response_PDU_t *);
PDUs_t * PDUset(SetRequest_PDU_t *);
PDUs_t * PDUinform(InformRequest_PDU_t *);
PDUs_t * PDUtrap(SNMPv2_Trap_PDU_t *);
PDUs_t * PDUreport(Report_PDU_t *);
asn_enc_rval_t encode(uint8_t *, size_t, PDUs_t *);
ANY_t * ANY(uint8_t *, asn_enc_rval_t);

#endif //