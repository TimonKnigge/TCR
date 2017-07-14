#include "../header.h"
#define RES_PHI (2 - ((1.0 + sqrt(5)) / 2.0))
#define EPSILON 1e-7

double gss(double (*f)(double), double leftbound, double rightbound) {
	double lb = leftbound, rb = rightbound, mlb = lb + RES_PHI * (rb - lb), mrb = rb + RES_PHI * (lb - rb);
	double lbv = f(lb), rbv = f(rb), mlbv = f(mlb), mrbv = f(mrb);

	while (rb - lb >= EPSILON) { // || abs(rbv - lbv) >= EPSILON) {
		if (mlbv < mrbv) { // > to maximize
			rb  = mrb;  rbv  = mrbv;
			mrb = mlb;  mrbv = mlbv;
			mlb = lb + RES_PHI * (rb - lb);
			mlbv = f(mlb);
		} else {
			lb  = mlb;  lbv  = mlbv;
			mlb = mrb;  mlbv = mrbv;
			mrb = rb + RES_PHI * (lb - rb);
			mrbv = f(mrb);
		}
	}
	return mlb; // any bound should do
}