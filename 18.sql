SELECT 
    visitor_type, -- Check if this matches your schema column name
    COUNT(*) AS total_visitors,
    CEIL(AVG(TIMESTAMPDIFF(SECOND, start_time, end_time))) AS avg_view_length_seconds -- Check start_time and end_time names
FROM 
    YOUR_ACTUAL_TABLE_NAME -- Replace 'YOUR_ACTUAL_TABLE_NAME' with the name found under Schema
GROUP BY 
    visitor_type
ORDER BY 
    visitor_type ASC;
