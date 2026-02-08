class InternSalaryCalculator : public SalaryCalculator {
public:
    double calculateSalary(const Employee& employee) override {
        return employee.baseSalary * 0.8;
    }
};
