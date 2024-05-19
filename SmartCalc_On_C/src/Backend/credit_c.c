#include "credit_c.h"

CreditOutput calculate_credit(CreditInput input) {
  CreditOutput res = {0};

  double p = input.loan_amount;
  double r = (long double)input.interest_rate;
  double n = (long double)input.term;

  if (input.is_yearly_frequency) n *= 12;

  if (input.is_annuity) {
    double m = r / 12 / 100;
    double c = ((m * pow(1 + m, n)) / (pow(1 + m, n) - 1));

    res.monthly_payment = p * c;
    res.overpayment = (res.monthly_payment * n) - p;
    res.total = res.monthly_payment * n;
  } else if (input.is_differentiated) {
    CreditPayment payment_plan[PAYMENT_PLAN_SIZE] = {0};

    double dept = p / n;
    double rest = p;

    for (int i = 0; i < n; ++i) {
      double days_in_month = 30.4166666667;

      payment_plan[i].payment_number = i + 1;
      payment_plan[i].repayment_of_principal = dept;
      payment_plan[i].interest_payment = rest * r / 100. * days_in_month / 365.;
      rest -= dept;
      payment_plan[i].rest = rest;
      payment_plan[i].payment = payment_plan[i].interest_payment + dept;
    }

    res.monthly_payment = payment_plan[0].payment;
    for (int i = 0; i < PAYMENT_PLAN_SIZE; ++i) {
      res.overpayment += payment_plan[i].interest_payment;

      if (payment_plan[i].payment)
        res.monthly_payment_last = payment_plan[i].payment;
    }
    res.total = res.overpayment + p;
  }

  if (isnan(res.total)) {
    res.monthly_payment = 0;
    res.monthly_payment_last = 0;
    res.overpayment = 0;
    res.total = 0;
  }

  return res;
}
