from requests import get, put, delete, post

TESTADRESS = 'http://127.0.0.1:1234/test'
APIADRESS = "http://127.0.0.1:1234/api/{}"

TABLE0 = "id\tvalue\n"
LINE = "item with id <{}> has been {}\n"
table = "{}\t{}\n"
old_table = ""
old_log = ""


def testing_put():
    global old_table
    global old_log
    id_num = 1
    command_name = "added"
    assert (put(APIADRESS.format(id_num)).status_code == 201)
    response = TABLE0 + table.format(id_num,0) + LINE.format(id_num, command_name)
    old_table += table.format(id_num,0)
    old_log += LINE.format(id_num, command_name)
    assert (get(TESTADRESS).text == response)

    id_num = 2
    command_name = "added"
    put(APIADRESS.format(id_num))
    response = TABLE0 + old_table + table.format(id_num,0) + old_log + LINE.format(id_num, command_name)
    old_table += table.format(id_num,0)
    old_log += LINE.format(id_num, command_name)
    assert (get(TESTADRESS).text == response)
    
    id_num = 2
    command_name = "added"
    put(APIADRESS.format(id_num))
    response = TABLE0 + old_table + old_log + LINE.format(id_num, command_name)
    old_log += LINE.format(id_num, command_name)
    assert (get(TESTADRESS).text == response)

def testing_post():
    global old_table
    global old_log
    old_table = table.format(1,0)
    id_num = 2
    command_name = "changed"
    post(APIADRESS.format(id_num))
    response = TABLE0 + old_table + table.format(id_num,1) + old_log + LINE.format(id_num, command_name)
    old_table += table.format(id_num,1)
    old_log += LINE.format(id_num, command_name)
    assert (get(TESTADRESS).text == response)

    id_num = 3
    command_name = "added"
    post(APIADRESS.format(id_num))
    response = TABLE0 + old_table + table.format(id_num,0) + old_log + LINE.format(id_num, command_name)
    old_table += table.format(id_num,0)
    old_log += LINE.format(id_num, command_name)
    assert (get(TESTADRESS).text == response)

def testing_get():
    begin = "{\n\t\"message\":\""
    ans = "Item id <{}>, item value <{}>."
    end = "\"\n}\n"
    id_num = 1
    response = begin + ans.format(id_num,0) + end
    assert (get(APIADRESS.format(id_num)).text == response)

    id_num = 2
    response = begin + ans.format(id_num,1) + end
    assert (get(APIADRESS.format(id_num)).text == response)

    ans = "Element <{}> not found."
    id_num = 5
    response = begin + ans.format(id_num) + end
    assert (get(APIADRESS.format(id_num)).text == response)

def testing_delete():
    global old_table
    global old_log
    old_table = table.format(2,1) + table.format(3,0)
    id_num = 1
    command_name = "deleted"
    assert (delete(APIADRESS.format(id_num)).status_code == 200)
    response = TABLE0 + old_table + old_log + LINE.format(id_num,command_name)
    #print(response)
    #print(get(TESTADRESS).text)
    assert (get(TESTADRESS).text == response)
