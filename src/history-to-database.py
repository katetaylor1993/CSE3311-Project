mport sqlite3, datetime
def fixDate(timestamp):
    #Chrome stores timestamps in the number of microseconds since Jan 1 1601.
    #To convert, we create a datetime object for Jan 1 1601...
    epoch_start = datetime.datetime(1601,1,1)
    #create an object for the number of microseconds in the timestamp
    delta = datetime.timedelta(microseconds=int(timestamp))
    #and return the sum of the two.
    return epoch_start + delta

selectStatement = 'SELECT target_path, referrer, start_time, end_time, received_bytes FROM downloads;'
historyFile = 'C:\\Users\\User\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\History'
c = sqlite3.connect(historyFile)
for row in c.execute(selectStatement):
    print "Download:",row[0].encode('utf-8')
    print "\tFrom:",str(row[1])
    print "\tStarted:",str(fixDate(row[2]))
    print "\tFinished:",str(fixDate(row[3]))
    print "\tSize:",str(row[4])
