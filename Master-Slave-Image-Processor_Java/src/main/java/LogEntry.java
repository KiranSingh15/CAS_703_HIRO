public class LogEntry {
    public final long threadId;
    public final String outputFilename;
    public final double duration; // in ms

    public LogEntry(long threadId, String outputFilename, double duration) {
        this.threadId = threadId;
        this.outputFilename = outputFilename;
        this.duration = duration;
    }
}