#ifndef CHART_H
#define CHART_H

#include <stdbool.h>
#include <sys/types.h>

/*
 * A chart is a set of N sampls of M distinct series, where all sampled values
 * are doubles representing either percentages or raw values. If values are
 * percentages, they are on the scale of 0-100, not 0-1, and the values for
 * all series for a given sample should sum to 100 (or reasonably close).
 *
 * The chart also contains a background color (for the whole chart) as well
 * as a color for each series.
 *
 * Example:
 * If you sample the 3 memory stats (% active/total/free) for 60 seconds,
 * you would want a chart with nseries = 3, nsamples = 60, and percents = true.
 */

typedef struct chart {
   size_t   nseries;    /* how many distinct series are in the chart    */
   size_t   nsamples;   /* how many samples of each series there are    */
   size_t   current;    /* index of current SAMPLE                      */
   bool     percents;   /* true = all values are percents, false = raw  */
   double **values;     /* the nseries x nsamples array of percents     */
   char    *bgcolor;    /* background color of the chart                */
   char   **colors;     /* array of nsamples - colors for each sample   */
} chart_t;

/*
 * Initialize a new chart object. The parameters are:
 *    nsamples    the number of distinct SAMPLES of each SERIES
 *    nseries     the number of each THINGS being tracked
 *    is_percents are the values percentages (0-1.0) or raw (any value)?
 *    bgcolor     string color (hex2rgba) for the background of the chart
 *    colors      array of colors for each series of the charts. There should
 *                be exactly NSERIES colors in this array.
 *
 * Example: to track the memory usage of a system for 10 seconds, we would do
 * the following...
 *    nseries     => 3 (we track total, active, and free memory)
 *    nsamples    => 10 (assuming we track 1 sample per second)
 *    is_percents => false (we track raw values as doubles, and let the chart
 *                   scale it. CPU usage is an example where you natively get
 *                   percentages)
 *    bgcolor     => "#444" (a nice gray background)
 *    colors      => [ "#f00", "#ff0", "#0f0" ] / an array of red/yellow/blue
 *                   to color the total/active/free memory.
 *                   XXX note that the color order sets the order of which
 *                   series should be added when updating.
 */
chart_t*
chart_init(
      size_t   nsamples,
      size_t   nseries,
      bool     is_percents,
      const char  *bgcolor,
      const char **colors);

/* Free all allocated memory with a chart */
void chart_free(chart_t *c);

/* Update a chart with an array of data, where size of data == c->nseries */
void chart_update(chart_t *c, double data[]);

/* Determine the min & max values in a chart's history (for scaling displays) */
void chart_get_minmax(chart_t *c, double *min, double *max);

/* Debug utility: print all data in a chart */
void chart_print(chart_t *c);

#endif
