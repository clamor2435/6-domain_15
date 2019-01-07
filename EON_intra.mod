/* Intra_domain.mod */

/*paramaters*/
param D integer, >0;
param R integer, >0;
param F integer, >0;
param N integer, >0;

/*Setting and variables*/

set DN := 1..D;
set RN := 1..R;
set NN := 1..N;
set FN := 0..(F-1);
set L within {DN,DN,NN,NN};

param v{DN,NN} integer;
param c{L} integer;

param s{RN} integer;
param d{RN} integer;
param r{RN} integer;

var x{RN,L,FN},binary;
var y{RN,L,FN},binary;
var p{RN,FN},binary;


minimize Index: sum{n in RN}(sum{f in FN}(sum{i in DN,k in NN,m in NN:(i,i,k,m) in L}y[n,i,i,k,m,f]));


s.t. FIRST_INDEX_1{n in RN,i in DN,k in NN,m in NN:(i,i,k,m) in L}:
    sum{f in FN}(x[n,i,i,k,m,f]) <=1;

s.t. FIRST_INDEX_2{n in RN,f in {0..(F - r[n])},fp in {f..(f+r[n]-1)},i in DN,k in NN,m in NN:(i,i,k,m) in L}:
    x[n,i,i,k,m,f] <= y[n,i,i,k,m,fp];

s.t. FIRST_INDEX_3{n in RN,i in DN, k in NN,m in NN,f in {(F - r[n]+1)..(F-1)}:(i,i,k,m) in L}:
x[n,i,i,k,m,f]=0;

s.t. INDEX_CONSTRAINT{i in DN,k in NN,m in NN,f in FN:(i,i,k,m) in L}:
	sum{n in RN}(y[n,i,i,k,m,f]) <= 1;

s.t. FIRST_INDEX_4{n in RN,i in DN,k in NN, m in NN:(i,i,k,m) in L}:
  sum{f in FN}(x[n,i,i,k,m,f]) = (1 / r[n])*sum{f in FN}(y[n,i,i,k,m,f]);

s.t. FLOW_CONSERVE_1{i in DN,k in NN,n in RN:v[i,k] = s[n]}:
	sum{f in FN}(sum{m in NN:(i,i,k,m) in L}y[n,i,i,k,m,f]) - sum{f in FN}(sum{m in NN:(i,i,m,k) in L}y[n,i,i,m,k,f])=r[n];

s.t. FLOW_CONSERVE_2{i in DN,k in NN,n in RN:v[i,k] = d[n]}:
	sum{f in FN}(sum{m in NN:(i,i,k,m) in L}y[n,i,i,k,m,f]) - sum{f in FN}(sum{m in NN:(i,i,m,k) in L}y[n,i,i,m,k,f])=-r[n];

s.t. FLOW_CONSERVE_3{i in DN,k in NN,n in RN:v[i,k] != s[n] && v[i,k] != d[n]}:
	sum{f in FN}(sum{m in NN:(i,i,k,m) in L}y[n,i,i,k,m,f]) - sum{f in FN}(sum{m in NN:(i,i,m,k) in L}y[n,i,i,m,k,f])=0;

s.t. LIMIT_SUM_INDEX{i in DN,k in NN,m in NN:(i,i,k,m) in L}:
	sum{f in FN}(sum{n in RN}(y[n,i,i,k,m,f])) <= F;

s.t. P_NF{i in DN,k in NN,n in RN,f in FN:(v[i,k] = s[n])}:
	p[n,f] = sum{m in NN:(i,i,k,m) in L}x[n,i,i,k,m,f];

s.t. INDEX_CONSISTENCE{i in DN, k in NN, m in NN,n in RN,f in FN:(i,i,k,m) in L}:
  p[n,f] >= x[n,i,i,k,m,f];
end;