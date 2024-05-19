#include "deposit_c.h"

DepositOutput calculate_deposit(DepositInput input) {
  DepositOutput res = {0};
  double interest_rate = input.interest_rate / 100;
  double tax_rate = input.tax_rate / 100;
  double deposit_amount = input.deposit_amount;

  unsigned int days = 0;
  for (int i = 0; i < (int)input.term; ++i) days += i % 2 == 0 ? 30 : 31;
  days = days - (days % 365);

  DepositPayment payment_plan[9999] = {0};

  for (int i = 0; i < (int)days; ++i) {
    payment_plan[i].day = i + 1;

    for (int j = 0; j < 5; ++j) {
      if (input.replenishments[j].day == payment_plan[i].day &&
          input.replenishments[j].replenishment) {
        payment_plan[i].replenishment = input.replenishments[j].replenishment;
        deposit_amount += input.replenishments[j].replenishment;
      }
      if (input.withdrawals[j].day == payment_plan[i].day &&
          input.withdrawals[j].withdrawal) {
        payment_plan[i].withdrawal = input.withdrawals[j].withdrawal;
        deposit_amount -= input.withdrawals[j].withdrawal;
      }
    }

    if (input.capitalization && input.is_daily_frequency)
      payment_plan[i].total_amount =
          deposit_amount * pow((1 + interest_rate / 365), payment_plan[i].day);
    else
      payment_plan[i].total_amount =
          deposit_amount * (1 + interest_rate / 365 * payment_plan[i].day);

    double total_earned = payment_plan[i].total_amount - deposit_amount;
    double total_earned_with_tax = total_earned - (total_earned * tax_rate);

    payment_plan[i].total_earned =
        (total_earned > TAX_FREE_AMOUNT) ? total_earned_with_tax : total_earned;
    payment_plan[i].tax_amount = (total_earned > TAX_FREE_AMOUNT)
                                     ? total_earned - total_earned_with_tax
                                     : 0;
    payment_plan[i].day_earned =
        deposit_amount * (1 + interest_rate / 365 * 1) - deposit_amount;
  }

  if (days > 0) {
    if (input.capitalization)
      res.total_earned = payment_plan[days - 1].total_earned;
    else
      for (int i = 0; i < 9999; ++i)
        res.total_earned += payment_plan[i].day_earned;

    res.total_amount = res.total_earned + deposit_amount;
    res.tax_amount = payment_plan[days - 1].tax_amount;
  }

  return res;
}
