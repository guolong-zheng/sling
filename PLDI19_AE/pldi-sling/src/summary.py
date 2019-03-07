import csv

with open('result.csv', mode='r') as infile, open('summary.csv', mode='w') as outfile:
    csv_reader = csv.reader(infile, delimiter=',')
    csv_writer = csv.writer(outfile, delimiter=',')
    total_line = 0
    program = ''
    num = 0
    loc = 0
    trace = 0
    inv = 0
    incomplete = 0
    time = 0
    single = 0
    pred = 0
    pure = 0
    csv_writer.writerow(['category','loc','trace','inv','incomplete','time','single','pred','pure'])
    
    for row in csv_reader:
        # loc#, traces#, inv#, time, single, pred, pure
        if row.strip() == '###':
            s = program.split('/')
            if len(s) == 4:
                category = s[2]
            else:
                category = s[2] + '/' + s[3]
            csv_writer.writerow([category, loc,trace,inv,incomplete,round(time,2),round(single/float(inv),2),round(pred/float(inv),2),round(pure/float(inv),2)])
            num = loc = trace = inv = incomplete = time = single = pred = pure = 0
        else:
            num += 1
            program = row['program']
            loc += int(row['loc'])
            trace += int(row['trace'])
            inv += int(row['inv'])
            incomplete += int(row['incomplete'])
            time += float(row['time'])
            single += int(row['single'])
            pred += int(row['pred'])
            pure += int(row['pure'])
        total_line += 1
