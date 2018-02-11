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

#endif //