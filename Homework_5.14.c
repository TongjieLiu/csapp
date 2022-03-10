/* A homework problem solution for the CS:APP3e

   Copyright (C) 2022 Tongjie Liu <tongjieandliu@gmail.com>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/* A.	Loop unrolling could only optimize the inner-loop to the latency
 * bound. Integer version has a latency bound of 1.00, and floating-point
 * number version has 3.00. These two are the only scalar versions existed.
 *
 *
 * B.	The floating-point number version was already at the latency bound,
 * and loop unrolling could only optimize the inner-loop to the latency
 * bound. */
#include <stdlib.h>
#include <stdio.h>




typedef double data_t;


typedef struct {
	long len;
	data_t *data;
} vec_rec, *vec_ptr;




vec_ptr new_vec(long len)
{
	vec_ptr result;
	data_t *data;
	

	result = (vec_ptr)malloc(sizeof(vec_rec));
	if (!result)
		return NULL;


	data = NULL;

	result->len = len;
	if (len > 0) {
		data = (data_t *)calloc(len, sizeof(data_t));
		if (!data) {
			free(result);
			return NULL;
		}
	}

	result->data = data;


	return result;
}


long vec_length(vec_ptr v)
{
	return v->len;
}


data_t *get_vec_start(vec_ptr v)
{
	return v->data;
}


int set_vec(vec_ptr v, long start)
{
	int i;
	long j;
	long len;
	data_t *data;


	if (v == NULL)
		return -1;


	len = vec_length(v);
	data = get_vec_start(v);

	for (i = 0, j = start; i < len; i++, j++)
		data[i] = j;
}




void original_inner(vec_ptr u, vec_ptr v, data_t *dest)
{
	long i;
	long length;
	data_t *udata, *vdata;
	data_t sum;


	length = vec_length(u);
	udata = get_vec_start(u);
	vdata = get_vec_start(v);
	sum = 0;


	for (i = 0; i < length; i++)
		sum = sum + udata[i] * vdata[i];


	*dest = sum;
}


void new_inner(vec_ptr u, vec_ptr v, data_t *dest)
{
	long i, limit;
	long length;
	data_t *udata, *vdata;
	data_t sum;


	length = vec_length(u);
	udata = get_vec_start(u);
	vdata = get_vec_start(v);
	sum = 0;


	/* i + 5 < length  =>  i < length - 5 */
	limit = length - 5;
	for (i = 0; i < limit; i += 6)
		sum = sum				+ \
		      udata[i] * vdata[i]		+ \
		      udata[i + 1] * vdata[i + 1]	+ \
		      udata[i + 2] * vdata[i + 2]	+ \
		      udata[i + 3] * vdata[i + 3]	+ \
		      udata[i + 4] * vdata[i + 4]	+ \
		      udata[i + 5] * vdata[i + 5];


	for (; i < length; i++)
		sum = sum + udata[i] * vdata[i];


	*dest = sum;
}




int main()
{
	vec_ptr u, v;
	data_t result;


	u = new_vec(20);
	v = new_vec(20);
	if (u == NULL || v == NULL) {
		puts("Couldn't create a new vector");
		exit(1);
	}


	set_vec(u, 1);
	set_vec(v, 5);


	original_inner(u, v, &result);
	printf("original: %f\n", (double)result);

	new_inner(u, v, &result);
	printf("new: %f\n", (double)result);


	return 0;
}
