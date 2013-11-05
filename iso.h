#ifndef __ISO_H__
#define __ISO_H__

/****************************************************************

iso.h

PLIK NAGLOWKOWY IMPLEMENTACJI ALGORYTMU DO BADANIA IZOMORFIZMU
DWOCH GRAFOW

*****************************************************************/

#define  MaxNodeNo   20

#define  true        1
#define  false       0
#define  MaxEdgeNo   (MaxNodeNo * (MaxNodeNo - 1) / 2)

typedef char boolean;

typedef char TByteRow[MaxNodeNo];

typedef struct _REC_TBoolRecArray {
    boolean Left, Right;
} _REC_TBoolRecArray;

typedef struct _REC_TByteRecArray {
    char Left, Right;
} _REC_TByteRecArray;

typedef _REC_TBoolRecArray TBoolRecArray[MaxNodeNo];
typedef _REC_TByteRecArray TByteRecArray[MaxNodeNo];


typedef boolean TAlTable[MaxNodeNo][MaxNodeNo];


typedef struct TGraph {
    TAlTable A;
    TByteRow Deg, DegSort;
} TGraph;

/* externals */
/*
void ConvertToComplement(TGraph *,
								 TGraph *,
								 int       );
*/

extern boolean EqualGraphs(int,
                           TGraph*,
                           TGraph*  );


#endif

/* end of iso.h */
