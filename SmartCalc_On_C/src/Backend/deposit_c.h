#ifndef DEPOSIT_C_H
#define DEPOSIT_C_H

/** @file */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Amount of free tax
 */
#define TAX_FREE_AMOUNT 160000

/**
 * @brief Item of deposit payment plan
 * @param day Day of item
 * @param total_amount Total amount
 * @param total_earned Total earned amount
 * @param day_earned Total earned amount
 * @param tax_amount Tax amount
 * @param replenishment List of replenishments
 * @param withdrawal List of withdrawls
 */
typedef struct DepositPayment {
  unsigned int day;
  double total_amount;
  double total_earned;
  double day_earned;
  double tax_amount;
  double replenishment;
  double withdrawal;
} DepositPayment;

/**
 * @brief Input struct for deposit
 * @param deposit_amount Deposit amount
 * @param term Term of deposit
 * @param interest_rate Interest rate
 * @param tax_rate Tax rate
 * @param is_daily_frequency Is daily frequency
 * @param is_ateoft_frequency Is at the end of term freaquency
 * @param capitalization Is capitalization enabled
 * @param replenishments Replenishment amount
 * @param withdrawals Withdrawal amount
 */
typedef struct DepositInput {
  double deposit_amount;
  unsigned int term;
  double interest_rate;
  double tax_rate;
  bool is_daily_frequency;
  bool is_ateoft_frequency;
  bool capitalization;
  DepositPayment replenishments[5];
  DepositPayment withdrawals[5];
} DepositInput;

/**
 * @brief Output struct for deposit
 * @param total_earned Total earned amount
 * @param tax_amount Tax amount
 * @param total_amount Total amount
 */
typedef struct DepositOutput {
  double total_earned;
  double tax_amount;
  double total_amount;
} DepositOutput;

DepositOutput calculate_deposit(DepositInput input);

#endif
