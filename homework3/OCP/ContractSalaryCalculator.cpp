class ContractSalaryCalculator : public SalaryCalculator {
public:
    double calculateSalary(const Employee& employee) override {
        return employee.baseSalary * 1.1;
    }
};
