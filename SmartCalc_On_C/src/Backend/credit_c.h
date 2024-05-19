#ifndef CREDIT_C_H
#define CREDIT_C_H

/** @file */

#include <math.h>
#include <stdbool.h>

/**
 * @brief Size of payment plan calendar
 */
#define PAYMENT_PLAN_SIZE 1024

/**
 * @brief Input struct for credit
 * @param loan_amount Credit amount
 * @param term Term of credit
 * @param is_monthly_frequency Is monthly frequency
 * @param is_yearly_frequency Is yearly frequency
 * @param interest_rate Interest rate
 * @param is_annuity Is allowed annuity
 * @param is_differentiated Is differentiated
 */
typedef struct CreditInput {
  double loan_amount;
  unsigned int term;
  bool is_monthly_frequency;
  bool is_yearly_frequency;
  double interest_rate;
  bool is_annuity;
  bool is_differentiated;
} CreditInput;

/**
 * @brief Output struct for credit
 * @param monthly_payment Payment of month
 * @param monthly_payment_last Payment of last month
 * @param overpayment Total ovepayment
 * @param total Total amount
 */
typedef struct CreditOutput {
  double monthly_payment;
  double monthly_payment_last;
  double overpayment;
  double total;
} CreditOutput;

/**
 * @brief Item of credit payment plan
 * @param payment_number index of payment
 * @param payment Payment amount
 * @param repayment_of_principal Repayment of principal
 * @param interest_payment Interset payment
 * @param rest Rest on account
 */
typedef struct CreditPayment {
  unsigned int payment_number;
  double payment;
  double repayment_of_principal;
  double interest_payment;
  double rest;
} CreditPayment;

/**
 * @brief Calculate credit
 * @param input CreditInput struct contains data for calculations
 * @return CreditOutput struct
 */
CreditOutput calculate_credit(CreditInput input);

#endif
