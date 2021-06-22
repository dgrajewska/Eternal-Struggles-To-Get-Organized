JSONObject json;

void setup() {
  String path = sketchPath() + "/data/data-protest.json";
  println(path);
  json = new JSONObject();

  json = loadJSONObject(path);
  JSONArray jsonStatuses = json.getJSONArray("statuses");
  
  for (int i = 0; i < jsonStatuses.size(); i++) {
    JSONObject statusObj = jsonStatuses.getJSONObject(i);
    String status = statusObj.getString("text");
    println(status);
  }
}
