def non_preemptive_sjf(processes, n):
    processes.sort(key=lambda x: x[1])
    completion_time = [0] * n
    for i in range(n):
        if i == 0:
            completion_time[i] = processes[i][1] + processes[i][2]
        else:
            completion_time[i] = completion_time[i-1] + processes[i][2]
    return completion_time

processes = [['P1', 0, 3], ['P2', 1, 5], ['P3', 2, 2], ['P4', 3, 3]]
n = len(processes)
completion_time = non_preemptive_sjf(processes, n)

print("Process Name\tArrival Time\tBurst Time\tCompletion Time")
for i in range(n):
    print(processes[i][0], "\t\t", processes[i][1], "\t\t", processes[i][2], "\t\t", completion_time[i])
