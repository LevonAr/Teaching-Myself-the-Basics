class objectTest():

    def __init__(self,a):

        self.value = a

    def get_value(self):

        return self.value
        
        
class execute():

    def __init__(self):

        a = objectTest(1)
        b = objectTest(1)

        print(a == b)
        print(a.get_value() == b.get_value)
        print(a.get_value() == b.get_value())
        print(a.get_value == b.get_value)
if __name__ == '__main__':

    execute = execute();

