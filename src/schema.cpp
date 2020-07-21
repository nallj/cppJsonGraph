#include <nlohmann/json.hpp>

// JSON Graph Schema v2
static nlohmann::json schema = R"(
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "$id": "http://jsongraphformat.info/v2.0/json-graph-schema.json",
  "title": "JSON Graph Schema",
  "oneOf": [
    {
      "type": "object",
      "properties": {
        "graph": {
          "$ref": "#/definitions/graph"
        }
      },
      "additionalProperties": false,
      "required": [
        "graph"
      ]
    },
    {
      "type": "object",
      "properties": {
        "graphs": {
          "type": "array",
          "items": {
            "$ref": "#/definitions/graph"
          }
        }
      },
      "additionalProperties": false
    }
  ],
  "definitions": {
    "graph": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": {
          "type": "string"
        },
        "label": {
          "type": "string"
        },
        "directed": {
          "type": [
            "boolean"
          ],
          "default": true
        },
        "type": {
          "type": "string"
        },
        "metadata": {
          "type": [
            "object"
          ]
        },
        "nodes": {
          "type": "object",
          "additionalProperties": {
            "type": "object",
            "properties": {
              "label": {
                "type": "string"
              },
              "metadata": {
                "type": "object"
              }
            },
            "additionalProperties": false
          }
        },
        "edges": {
          "type": [
            "array"
          ],
          "items": {
            "type": "object",
            "additionalProperties": false,
            "properties": {
              "id": {
                "type": "string"
              },
              "source": {
                "type": "string"
              },
              "target": {
                "type": "string"
              },
              "relation": {
                "type": "string"
              },
              "directed": {
                "type": [
                  "boolean"
                ],
                "default": true
              },
              "label": {
                "type": "string"
              },
              "metadata": {
                "type": [
                  "object"
                ]
              }
            },
            "required": [
              "source",
              "target"
            ]
          }
        }
      }
    }
  }
}
)"_json;
