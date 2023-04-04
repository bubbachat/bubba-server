CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    username character varying(255) NOT NULL,
    created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    updated_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP NOT NULL
);
