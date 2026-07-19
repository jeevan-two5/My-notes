SELECT 
    visitor_type,
    COUNT(visitor_type) AS total_visitors,
    CEIL(AVG(TIMESTAMPDIFF(SECOND, start_time, end_time))) AS avg_view_length_seconds
FROM 
    views
GROUP BY 
    visitor_type
ORDER BY 
    visitor_type ASC;
