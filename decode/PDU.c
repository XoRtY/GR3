/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SNMPv2-PDU"
 * 	found in "snmpv2c.asn1"
 */

#include "PDU.h"

static int
memb_request_id_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -214783648 && value <= 214783647)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_error_index_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 2147483647)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_request_id_constr_2 CC_NOTUSED = {
	{ 4, 0 }	/* (-214783648..214783647) */,
	-1};
static asn_per_constraints_t asn_PER_memb_request_id_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 29, -1, -214783648,  214783647 }	/* (-214783648..214783647) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_error_index_constr_23 CC_NOTUSED = {
	{ 4, 1 }	/* (0..2147483647) */,
	-1};
static asn_per_constraints_t asn_PER_memb_error_index_constr_23 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 31, -1,  0,  2147483647 }	/* (0..2147483647) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_PDU_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, request_id),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_request_id_constr_2, &asn_PER_memb_request_id_constr_2,  memb_request_id_constraint_1 },
		0, 0, /* No default value */
		"request-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, error_status),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"error-status"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, error_index),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_error_index_constr_23, &asn_PER_memb_error_index_constr_23,  memb_error_index_constraint_1 },
		0, 0, /* No default value */
		"error-index"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, variable_bindings),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_VarBindList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"variable-bindings"
		},
};
static const ber_tlv_tag_t asn_DEF_PDU_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PDU_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 2 }, /* request-id */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, -1, 1 }, /* error-status */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -2, 0 }, /* error-index */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 3, 0, 0 } /* variable-bindings */
};
asn_SEQUENCE_specifics_t asn_SPC_PDU_specs_1 = {
	sizeof(struct PDU),
	offsetof(struct PDU, _asn_ctx),
	asn_MAP_PDU_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PDU = {
	"PDU",
	"PDU",
	&asn_OP_SEQUENCE,
	asn_DEF_PDU_tags_1,
	sizeof(asn_DEF_PDU_tags_1)
		/sizeof(asn_DEF_PDU_tags_1[0]), /* 1 */
	asn_DEF_PDU_tags_1,	/* Same as above */
	sizeof(asn_DEF_PDU_tags_1)
		/sizeof(asn_DEF_PDU_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PDU_1,
	4,	/* Elements count */
	&asn_SPC_PDU_specs_1	/* Additional specs */
};

