#include <stdio.h>
#include <malloc.h> 
#include "index_min_pri_qun.h"


static void index_qun_exch(index_min_qun *i_q, int i, int j)
{
	int tmp;
	tmp = i_q->pq[i];
	i_q->pq[i] = i_q->pq[j];
	i_q->pq[j] = tmp;

	i_q->qp[i_q->pq[i]] = i;
	i_q->qp[i_q->pq[j]] = j;
}

static inline void index_qun_less(index_min_qun *i_q, int i, int j)
{
	return i_q->qun_p[i_q->pq[i]] < i_q->qun_p[i_q->pq[j]]? 1 : 0;
}


#if 0
main()
{
	index_min_qun i_qun;
	int qun[20] = { 0 };
	int pq[20] = { -1 };
	int qp[20] = { -1 };

	i_qun.num = 0;
	i_qun.qun_p = qun;
	i_qun.pq = pq;
	i_qun.qp = qp;

	

	
}

#endif

