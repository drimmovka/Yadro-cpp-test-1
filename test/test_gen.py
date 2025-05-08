import random

def generate_tests():    
    for i in range(15):
        count_numbers = random.randint(10, 10000)
        numbers = [random.randint(-10000, 10000) for _ in range(count_numbers)]
        
        test_filename = f"tests/test_{i+1}.txt"
        with open(test_filename, "w") as f:
            f.write(" ".join(map(str, numbers)) + " ")
        
        answer_filename = f"answers/ans_{i+1}.txt"
        with open(answer_filename, "w") as f:
            f.write(" ".join(map(str, sorted(numbers))) + " ")

if __name__ == "__main__":
    generate_tests()