#include "../include/suiteMethod.h"

double Frequency(int n)
{
	int		i;
	double	f, s_obs, p_value, sum, sqrt2 = 1.41421356237309504880;
	
	sum     = 0.0;
	for ( i=0; i<n; i++ )
		sum += 2*(int)epsilon[i]-1;

	s_obs   = fabs(sum)/sqrt(n);
	f       = s_obs/sqrt2;
	p_value = erfc(f);

	return p_value;
}

double BlockFrequency(int M, int n)
{
	int		i, j, N, blockSum;
	double	p_value, sum, pi, v, chi_squared;
	
	N = n/M; 		/* # OF SUBSTRING BLOCKS      */
	sum = 0.0;
	
	for ( i=0; i<N; i++ ) {
		blockSum = 0;
		for ( j=0; j<M; j++ )
			blockSum += epsilon[j+i*M];
		pi = (double)blockSum/(double)M;
		v = pi - 0.5;
		sum += v*v;
	}
	chi_squared = 4.0 * M * sum;
	p_value = cephes_igamc(N/2.0, chi_squared/2.0);

	return p_value;
}

double Runs(int n)
{
	int		S, k;
	double	pi, V, erfc_arg, p_value;

	S = 0;
	for ( k=0; k<n; k++ )
		if ( epsilon[k] )
			S++;
	pi = (double)S / (double)n;

	if ( fabs(pi - 0.5) > (2.0 / sqrt(n)) ) {
		p_value = 0.0;
	}
	else {

		V = 1;
		for ( k=1; k<n; k++ )
			if ( epsilon[k] != epsilon[k-1] )
				V++;
	
		erfc_arg = fabs(V - 2.0 * n * pi * (1-pi)) / (2.0 * pi * (1-pi) * sqrt(2*n));
		p_value = erfc(erfc_arg);
		
	}


	return p_value;
}

double LongestRunOfOnes(int n)
{
	double			pval, chi2, pi[7];
	int			run, v_n_obs, N, i, j, K, M, V[7];
	unsigned int	nu[7] = { 0, 0, 0, 0, 0, 0, 0 };

	if ( n < 128 ) {
		return 0.0;
	}
	if ( n < 6272 ) {
		K = 3;
		M = 8;
		V[0] = 1; V[1] = 2; V[2] = 3; V[3] = 4;
		pi[0] = 0.21484375;
		pi[1] = 0.3671875;
		pi[2] = 0.23046875;
		pi[3] = 0.1875;
	}
	else if ( n < 750000 ) {
		K = 5;
		M = 128;
		V[0] = 4; V[1] = 5; V[2] = 6; V[3] = 7; V[4] = 8; V[5] = 9;
		pi[0] = 0.1174035788;
		pi[1] = 0.242955959;
		pi[2] = 0.249363483;
		pi[3] = 0.17517706;
		pi[4] = 0.102701071;
		pi[5] = 0.112398847;
	}
	else {
		K = 6;
		M = 10000;
		V[0] = 10; V[1] = 11; V[2] = 12; V[3] = 13; V[4] = 14; V[5] = 15; V[6] = 16;
		pi[0] = 0.0882;
		pi[1] = 0.2092;
		pi[2] = 0.2483;
		pi[3] = 0.1933;
		pi[4] = 0.1208;
		pi[5] = 0.0675;
		pi[6] = 0.0727;
	}
	
	N = n/M;
	for ( i=0; i<N; i++ )
	{
		v_n_obs = 0;
		run = 0;
		for ( j=0; j<M; j++ )
		{
			if ( epsilon[i*M+j] == 1 ) 
			{
				run++;
				if ( run > v_n_obs )
					v_n_obs = run;
			}
			else
				run = 0;
		}

		if ( v_n_obs < V[0] )
			nu[0]++;
		
		for ( j=0; j<=K; j++ ) 
		{
			if ( v_n_obs == V[j] )
				nu[j]++;
		}
		
		if ( v_n_obs > V[K] )
			nu[K]++;
	}

	chi2 = 0.0;
	for ( i=0; i<=K; i++ )
		chi2 += ((nu[i] - N * pi[i]) * (nu[i] - N * pi[i])) / (N * pi[i]);

	pval = cephes_igamc((double)(K/2.0), chi2 / 2.0);

	return pval;

}


double Rank(int n)
{
	int		N, i, k, r;
	double		p_value, product, chi_squared, arg1, p_32, p_31, p_30, R, F_32, F_31, F_30;
	BitSequence	**matrix = create_matrix(32, 32);
	
	N = n/(32*32);
	if ( isZero(N) ) {
		p_value = 0.00;
	}
	else {
		r = 32;					// COMPUTE PROBABILITIES 
		product = 1;
		for ( i=0; i<=r-1; i++ )
			product *= ((1.e0-pow(2, i-32))*(1.e0-pow(2, i-32)))/(1.e0-pow(2, i-r));
		p_32 = pow(2, r*(32+32-r)-32*32) * product;
		
		r = 31;
		product = 1;
		for ( i=0; i<=r-1; i++ )
			product *= ((1.e0-pow(2, i-32))*(1.e0-pow(2, i-32)))/(1.e0-pow(2, i-r));
		p_31 = pow(2, r*(32+32-r)-32*32) * product;
		
		p_30 = 1 - (p_32+p_31);
		
		F_32 = 0;
		F_31 = 0;
		for ( k=0; k<N; k++ ) {			// FOR EACH 32x32 MATRIX   
			def_matrix(32, 32, matrix, k);
#if (DISPLAY_MATRICES == 1)
			display_matrix(32, 32, matrix);
#endif
			R = computeRank(32, 32, matrix);
			if ( R == 32 )
				F_32++;			// DETERMINE FREQUENCIES 
			if ( R == 31 )
				F_31++;
		}
		F_30 = (double)N - (F_32+F_31);
		
		chi_squared =(pow(F_32 - N*p_32, 2)/(double)(N*p_32) +
					  pow(F_31 - N*p_31, 2)/(double)(N*p_31) +
					  pow(F_30 - N*p_30, 2)/(double)(N*p_30));
		
		arg1 = -chi_squared/2.e0;

		p_value = exp(arg1);
		if ( isNegative(p_value) || isGreaterThanOne(p_value) )
 			p_value = 0.0;

		for ( i=0; i<32; i++ )				// DEALLOCATE MATRIX  
			free(matrix[i]);
		free(matrix);
	}

	return p_value;
}

double ApproximateEntropy(int m, int n)
{
	int		i, j, k, r, blockSize, seqLength, powLen, index;
	double		sum, numOfBlocks, ApEn[2], apen, chi_squared, p_value;
	unsigned int	*P;
	
	seqLength = n;
	r = 0;
	
	for ( blockSize=m; blockSize<=m+1; blockSize++ ) {
		if ( blockSize == 0 ) {
			ApEn[0] = 0.00;
			r++;
		}
		else {
			numOfBlocks = (double)seqLength;
			powLen = (int)pow(2, blockSize+1)-1;
			if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL ) {
				return 0.0;
			}
			for ( i=1; i<powLen-1; i++ )
				P[i] = 0;
			for ( i=0; i<numOfBlocks; i++ ) { // COMPUTE FREQUENCY 
				k = 1;
				for ( j=0; j<blockSize; j++ ) {
					k <<= 1;
					if ( (int)epsilon[(i+j) % seqLength] == 1 )
						k++;
				}
				P[k-1]++;
			}
			//DISPLAY FREQUENCY 
			sum = 0.0;
			index = (int)pow(2, blockSize)-1;
			for ( i=0; i<(int)pow(2, blockSize); i++ ) {
				if ( P[index] > 0 )
					sum += P[index]*log(P[index]/numOfBlocks);
				index++;
			}
			sum /= numOfBlocks;
			ApEn[r] = sum;
			r++;
			free(P);
		}
	}
	apen = ApEn[0] - ApEn[1];
	
	chi_squared = 2.0*seqLength*(log(2) - apen);
	p_value = cephes_igamc(pow(2, m-1), chi_squared/2.0);
	
	return p_value;
}

void  __ogg_fdrffti(int n, double *wsave, int *ifac);
void  __ogg_fdrfftf(int n, double *X, double *wsave, int *ifac);

double DiscreteFourierTransform(int n)
{
	double	p_value, upperBound, percentile, N_l, N_o, d, *m, *X, *wsave;
	int		i, count, ifac[15];

	if ( ((X = (double*) calloc(n,sizeof(double))) == NULL) ||
		 ((wsave = (double *)calloc(2*n,sizeof(double))) == NULL) ||
		 ((m = (double*)calloc(n/2+1, sizeof(double))) == NULL) ) {
			if( X == NULL )
				free(X);
			if( wsave == NULL )
				free(wsave);
			if( m == NULL )
				free(m);
			return 0.0;
	}
	for ( i=0; i<n; i++ )
		X[i] = 2*(int)epsilon[i] - 1;
	
	__ogg_fdrffti(n, wsave, ifac);		// INITIALIZE WORK ARRAYS 
	__ogg_fdrfftf(n, X, wsave, ifac);	// APPLY FORWARD FFT 
	
	m[0] = sqrt(X[0]*X[0]);	    // COMPUTE MAGNITUDE 
	
	for ( i=0; i<n/2; i++ )
		m[i+1] = sqrt(pow(X[2*i+1],2)+pow(X[2*i+2],2)); 
	count = 0;				       // CONFIDENCE INTERVAL 
	upperBound = sqrt(2.995732274*n);
	for ( i=0; i<n/2; i++ )
		if ( m[i] < upperBound )
			count++;
	percentile = (double)count/(n/2)*100;
	N_l = (double) count;       // number of peaks less than h = sqrt(3*n) 
	N_o = (double) 0.95*n/2.0;
	d = (N_l - N_o)/sqrt(n/4.0*0.95*0.05);
	p_value = erfc(fabs(d)/sqrt(2.0));


	free(X);
	free(wsave);
	free(m);
	return p_value;
}
























