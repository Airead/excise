#ifndef _STRGEN_H_
#define _STRGEN_H_

struct strgen_dev {
	int quantum;              /* the current quantum size */
	int qset;                 /* the current array size */
	unsigned long size;       /* amount of data stored here */
	unsigned int access_key;  /* used by sculluid and scullpriv */
	struct cdev cdev;	  /* Char device structure		*/
};


#endif /* _STRGEN_H_ */
