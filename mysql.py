'''
Created on 2020年1月30日

@author: JM
'''
import pandas as pd
import tushare as ts
from sqlalchemy import create_engine 

engine_ts = create_engine('mysql://root:921332@localhost/stock?charset=utf8&use_unicode=1')

def read_data():
    sql = """SELECT * FROM today_all LIMIT 20"""
    df = pd.read_sql_query(sql, engine_ts)
    return df


def write_data(df):
    res = df.to_sql('today_all', engine_ts, index=False, if_exists='append', chunksize=5000)
    print(res)


def get_data():
    pro = ts.pro_api()
    df = ts.get_today_all()
    return df


if __name__ == '__main__':
#     df = read_data()
    df = get_data()
    write_data(df)
    print(df)