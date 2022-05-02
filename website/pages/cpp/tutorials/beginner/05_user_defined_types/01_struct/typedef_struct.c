struct point {
	int x;
	int y;
};
/* because "tag space" and global "name space" are separate,
   they can use identical identifiers */
typedef struct point point;

/* shorter form, without providing tag name */
typedef struct {
	int x;
	int y;
} point;
