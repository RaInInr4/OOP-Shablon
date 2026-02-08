// Абстрактный класс
class SalaryCalculator {
public:
    virtual double calculateSalary(const Employee& employee) = 0;
    virtual ~SalaryCalculator() {}
};
