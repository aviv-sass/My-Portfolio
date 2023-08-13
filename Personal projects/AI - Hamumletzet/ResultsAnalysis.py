import pandas as pd
import os
import glob
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

# merge csv files
def merge_csv_files(directory):
    file_extension = '.csv'
    csv_files = glob.glob(os.path.join(f'experiments/{directory}', f'*{file_extension}'))

    data = []

    for file in csv_files:
        df = pd.read_csv(file)
        data.append(df)

    merged_data = pd.concat(data, ignore_index=True, keys=None)

    # Sort the merged data by the 'id' column
    merged_data = merged_data.sort_values(by='id')

    output_file = f'experiments/merged_results_{directory}.csv'
    merged_data.to_csv(output_file, index=False, encoding="utf-8-sig")


def analayse_tuning_exp(directory):
    # merge_csv_files(directory)
    # data = pd.read_csv(f'experiments/merged_results_{directory}.csv', low_memory=False) # low_memory=False to avoid DtypeWarning
    data = pd.read_csv(f'experiments/merged_results_{directory}.csv')
    # credit_left_groups = [(0, 23), (24, 46), (47, 79), (80, 112), (113, 200)]
    credit_left_groups = [(118.5, 120), (7.5,30), (34.5,51.5), (52,64), (73.5,81), (95.5,100)]
    # credit_left_groups = [(118,101), (100, 95), (82, 72), (64, 49), (46, 26), (28, 3)]
    for group in credit_left_groups:
        group_data = data.loc[(data['credit left'] >= group[0]) & (data['credit left'] <= group[1])].copy()

        group_timedout_data = group_data.loc[group_data['A*_1 description'] == 'timedout'].copy()
        group_not_timedout_data = group_data.loc[group_data['A*_1 description'] != 'timedout'].copy()

        column_names = [f"A*_{i} semester count" for i in range(1, 7)]
        group_not_timedout_data.loc[:, column_names] = group_not_timedout_data.loc[:, column_names].astype(float)
        group_not_timedout_data['mean semester count'] = group_not_timedout_data.loc[:, column_names].mean(axis=1)
        columns_of_interest = ['academic background', 'max available courses', 'mean semester count']
        group_not_timedout_data = group_not_timedout_data[columns_of_interest]
        # Set the figure size before creating the bar plot
        plt.figure(figsize=(40, 15))  # Adjust the width and height as desired

        ax = sns.barplot(
            data=group_not_timedout_data,
            x='academic background',
            y='mean semester count',
            hue='max available courses',
            palette='viridis'
        )

        plt.ylim(0, 10)
        plt.xlabel('Academic Background')
        plt.ylabel('Mean Semester Count')
        plt.title(f'Mean Semester Count by Academic Background credit left {group}')
        ax.set_xticklabels(ax.get_xticklabels(), rotation=45, ha='right')  # Adjust rotation and alignment
        plt.tight_layout()
        # save the figure before showing it
        plt.savefig(f'{directory}_credit_left_{group[0]}_{group[1]}.png')
        plt.show()

analayse_tuning_exp('tuning_exp_results - 10 students from Gen1 - max = 6,7,8,...,14,15 - Timeout = 30m')
# analayse_tuning_exp_by_time('tuning_exp_results - 10 students from Gen2 - max = 6,7,8,...,14,15 - Timeout = 30m')

